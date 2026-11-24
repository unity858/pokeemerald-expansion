#include "global.h"
#include "new_game_options.h"
#include "bg.h"
#include "difficulty.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "international_string_util.h"
#include "main.h"
#include "main_menu.h"
#include "menu.h"
#include "palette.h"
#include "scanline_effect.h"
#include "sound.h"
#include "sprite.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "window.h"
#include "constants/flags.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/vars.h"

/*
 * New game "Game options" screen.
 *
 * Shown after NEW GAME is picked on the main menu and before Birch's speech.
 * Layout, palettes, window frames and the row highlight mirror the in-game
 * Options menu (src/option_menu.c).
 *
 * The choices are kept in sPendingOptions (not in the save) until the game
 * actually starts: NewGameInitData (called from CB2_NewGame at the end of the
 * Birch speech) clears every flag and var, so CB2_NewGame calls
 * NewGameOptions_ApplyToSave right after it.
 */

enum
{
    MENUITEM_DIFFICULTY,
    MENUITEM_DATAMODE,
    MENUITEM_PERFECT_IVS,
    MENUITEM_OK,
    MENUITEM_COUNT,
};

enum
{
    WIN_HEADER,
    WIN_OPTIONS,
};

enum
{
    CHOICE_EASY,
    CHOICE_MEDIUM,
    CHOICE_HARD,
    CHOICE_DIFFICULTY_COUNT,
};

#define tMenuSelection  data[0]
#define tDifficulty     data[1]
#define tDataMode       data[2]
#define tPerfectIvs     data[3]

// One 16px row per menu item plus the note line
#define OPTIONS_WIN_HEIGHT ((MENUITEM_COUNT + 1) * 2)

#define YPOS_DIFFICULTY (MENUITEM_DIFFICULTY * 16)
#define YPOS_DATAMODE   (MENUITEM_DATAMODE * 16)
#define YPOS_PERFECTIVS (MENUITEM_PERFECT_IVS * 16)
#define YPOS_NOTE       (MENUITEM_COUNT * 16)

#define CHOICES_LEFT    96
#define CHOICES_RIGHT   198

struct PendingNewGameOptions
{
    bool8 chosen;
    u8 difficulty; // enum DifficultyLevel
    u8 dataMode;   // enum NewGameDataMode
    bool8 perfectIvs;
};

// Not part of the save. Holds the choices until NewGameInitData has run.
EWRAM_DATA static struct PendingNewGameOptions sPendingOptions = {0};

static void Task_NewGameOptionsFadeIn(u8 taskId);
static void Task_NewGameOptionsProcessInput(u8 taskId);
static void Task_NewGameOptionsFadeOutToBirch(u8 taskId);
static void Task_NewGameOptionsFadeOutToMainMenu(u8 taskId);
static void HighlightNewGameOptionsItem(u8 index);
static void Difficulty_DrawChoices(u8 selection);
static void DataMode_DrawChoices(u8 selection);
static void PerfectIvs_DrawChoices(u8 selection);
static void DrawHeaderText(void);
static void DrawNewGameOptionsTexts(void);
static void DrawBgWindowFrames(void);

static const u8 sText_GameOptions[] = _("GAME OPTIONS");
static const u8 sText_Easy[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}EASY");
static const u8 sText_Medium[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}MEDIUM");
static const u8 sText_Hard[]        = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}HARD");
static const u8 sText_Vanilla[]     = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}VANILLA");
static const u8 sText_Custom[]      = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}CUSTOM");
static const u8 sText_Off[]         = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}OFF");
static const u8 sText_On[]          = _("{COLOR GREEN}{SHADOW LIGHT_GREEN}ON");
static const u8 sText_Note[]        = _("These can't be changed later.");

static const u8 *const sNewGameOptionsItemNames[MENUITEM_COUNT] =
{
    [MENUITEM_DIFFICULTY] = COMPOUND_STRING("DIFFICULTY"),
    [MENUITEM_DATAMODE]   = COMPOUND_STRING("DATA"),
    [MENUITEM_PERFECT_IVS] = COMPOUND_STRING("PERFECT IVS"),
    [MENUITEM_OK]         = COMPOUND_STRING("OK"),
};

static const u8 sChoiceToDifficulty[CHOICE_DIFFICULTY_COUNT] =
{
    [CHOICE_EASY]   = DIFFICULTY_EASY,
    [CHOICE_MEDIUM] = DIFFICULTY_NORMAL,
    [CHOICE_HARD]   = DIFFICULTY_HARD,
};

static const u16 sOptionMenuText_Pal[] = INCGFX_U16("graphics/interface/option_menu_text.pal", ".gbapal");
static const u16 sOptionMenuBg_Pal[] = {RGB(17, 18, 31)};

static const struct WindowTemplate sNewGameOptionsWinTemplates[] =
{
    [WIN_HEADER] = {
        .bg = 1,
        .tilemapLeft = 2,
        .tilemapTop = 1,
        .width = 26,
        .height = 2,
        .paletteNum = 1,
        .baseBlock = 2
    },
    [WIN_OPTIONS] = {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 5,
        .width = 26,
        .height = OPTIONS_WIN_HEIGHT,
        .paletteNum = 1,
        .baseBlock = 0x36
    },
    DUMMY_WIN_TEMPLATE
};

static const struct BgTemplate sNewGameOptionsBgTemplates[] =
{
    {
        .bg = 1,
        .charBaseIndex = 1,
        .mapBaseIndex = 30,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },
    {
        .bg = 0,
        .charBaseIndex = 1,
        .mapBaseIndex = 31,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 1,
        .baseTile = 0
    }
};

// ---------------------------------------------------------------------------
// Public accessors

void NewGameOptions_ApplyToSave(void)
{
    u8 difficulty = DIFFICULTY_NORMAL;
    u8 dataMode = DATA_MODE_VANILLA;
    bool8 perfectIvs = FALSE;

    if (sPendingOptions.chosen)
    {
        if (sPendingOptions.difficulty <= DIFFICULTY_HARD)
            difficulty = sPendingOptions.difficulty;
        if (sPendingOptions.dataMode < DATA_MODE_COUNT)
            dataMode = sPendingOptions.dataMode;
        perfectIvs = (sPendingOptions.perfectIvs != FALSE);
    }

    SetCurrentDifficultyLevel(difficulty);
#ifdef FLAG_CUSTOM_DATA_MODE
    if (dataMode == DATA_MODE_CUSTOM)
        FlagSet(FLAG_CUSTOM_DATA_MODE);
    else
        FlagClear(FLAG_CUSTOM_DATA_MODE);
#endif
#ifdef FLAG_PERFECT_IV_MODE
    if (perfectIvs)
        FlagSet(FLAG_PERFECT_IV_MODE);
    else
        FlagClear(FLAG_PERFECT_IV_MODE);
#endif

    // Consumed; a later new game must go through the screen again.
    sPendingOptions.chosen = FALSE;
}

bool32 IsCustomDataMode(void)
{
#ifdef FLAG_CUSTOM_DATA_MODE
    return FlagGet(FLAG_CUSTOM_DATA_MODE);
#else
    return FALSE;
#endif
}

enum NewGameDataMode GetDataMode(void)
{
    return IsCustomDataMode() ? DATA_MODE_CUSTOM : DATA_MODE_VANILLA;
}

bool32 IsPerfectIvMode(void)
{
#ifdef FLAG_PERFECT_IV_MODE
    return FlagGet(FLAG_PERFECT_IV_MODE);
#else
    return FALSE;
#endif
}

// ---------------------------------------------------------------------------
// Screen

static void MainCB2(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void CB2_InitNewGameOptions(void)
{
    switch (gMain.state)
    {
    default:
    case 0:
        SetVBlankCallback(NULL);
        gMain.state++;
        break;
    case 1:
        DmaClearLarge16(3, (void *)(VRAM), VRAM_SIZE, 0x1000);
        DmaClear32(3, OAM, OAM_SIZE);
        DmaClear16(3, PLTT, PLTT_SIZE);
        SetGpuReg(REG_OFFSET_DISPCNT, 0);
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sNewGameOptionsBgTemplates, ARRAY_COUNT(sNewGameOptionsBgTemplates));
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);
        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(2, 0, BG_COORD_SET);
        ChangeBgY(2, 0, BG_COORD_SET);
        ChangeBgX(3, 0, BG_COORD_SET);
        ChangeBgY(3, 0, BG_COORD_SET);
        InitWindows(sNewGameOptionsWinTemplates);
        DeactivateAllTextPrinters();
        SetGpuReg(REG_OFFSET_WIN0H, 0);
        SetGpuReg(REG_OFFSET_WIN0V, 0);
        SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG0);
        SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG0 | WINOUT_WIN01_BG1 | WINOUT_WIN01_CLR);
        SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_DARKEN);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetGpuReg(REG_OFFSET_BLDY, 4);
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_WIN0_ON | DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        ShowBg(0);
        ShowBg(1);
        gMain.state++;
        break;
    case 2:
        ResetPaletteFade();
        ScanlineEffect_Stop();
        ResetTasks();
        ResetSpriteData();
        gMain.state++;
        break;
    case 3:
        LoadBgTiles(1, GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->tiles, 0x120, 0x1A2);
        gMain.state++;
        break;
    case 4:
        LoadPalette(sOptionMenuBg_Pal, BG_PLTT_ID(0), sizeof(sOptionMenuBg_Pal));
        LoadPalette(GetWindowFrameTilesPal(gSaveBlock2Ptr->optionsWindowFrameType)->pal, BG_PLTT_ID(7), PLTT_SIZE_4BPP);
        gMain.state++;
        break;
    case 5:
        LoadPalette(sOptionMenuText_Pal, BG_PLTT_ID(1), sizeof(sOptionMenuText_Pal));
        gMain.state++;
        break;
    case 6:
        PutWindowTilemap(WIN_HEADER);
        DrawHeaderText();
        gMain.state++;
        break;
    case 7:
        PutWindowTilemap(WIN_OPTIONS);
        DrawNewGameOptionsTexts();
        gMain.state++;
        break;
    case 8:
        DrawBgWindowFrames();
        gMain.state++;
        break;
    case 9:
    {
        u8 taskId = CreateTask(Task_NewGameOptionsFadeIn, 0);

        // Defaults: Medium / Vanilla / Perfect IVs off
        gTasks[taskId].tMenuSelection = MENUITEM_DIFFICULTY;
        gTasks[taskId].tDifficulty = CHOICE_MEDIUM;
        gTasks[taskId].tDataMode = DATA_MODE_VANILLA;
        gTasks[taskId].tPerfectIvs = FALSE;
        sPendingOptions.chosen = FALSE;

        Difficulty_DrawChoices(gTasks[taskId].tDifficulty);
        DataMode_DrawChoices(gTasks[taskId].tDataMode);
        PerfectIvs_DrawChoices(gTasks[taskId].tPerfectIvs);
        HighlightNewGameOptionsItem(gTasks[taskId].tMenuSelection);

        CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
        gMain.state++;
        break;
    }
    case 10:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        SetVBlankCallback(VBlankCB);
        SetMainCallback2(MainCB2);
        return;
    }
}

static void Task_NewGameOptionsFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_NewGameOptionsProcessInput;
}

static void Task_NewGameOptionsProcessInput(u8 taskId)
{
    s16 *data = gTasks[taskId].data;

    if (JOY_NEW(A_BUTTON) && tMenuSelection != MENUITEM_OK)
    {
        // A on an option row advances to the next row, ending on OK
        tMenuSelection++;
        HighlightNewGameOptionsItem(tMenuSelection);
    }
    else if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        sPendingOptions.difficulty = sChoiceToDifficulty[tDifficulty];
        sPendingOptions.dataMode = tDataMode;
        sPendingOptions.perfectIvs = tPerfectIvs;
        sPendingOptions.chosen = TRUE;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_NewGameOptionsFadeOutToBirch;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        sPendingOptions.chosen = FALSE;
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_NewGameOptionsFadeOutToMainMenu;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (tMenuSelection > 0)
            tMenuSelection--;
        else
            tMenuSelection = MENUITEM_COUNT - 1;
        HighlightNewGameOptionsItem(tMenuSelection);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (tMenuSelection < MENUITEM_COUNT - 1)
            tMenuSelection++;
        else
            tMenuSelection = 0;
        HighlightNewGameOptionsItem(tMenuSelection);
    }
    else if (JOY_NEW(DPAD_LEFT | DPAD_RIGHT))
    {
        switch (tMenuSelection)
        {
        case MENUITEM_DIFFICULTY:
            if (JOY_NEW(DPAD_RIGHT))
                tDifficulty = (tDifficulty < CHOICE_DIFFICULTY_COUNT - 1) ? tDifficulty + 1 : 0;
            else
                tDifficulty = (tDifficulty > 0) ? tDifficulty - 1 : CHOICE_DIFFICULTY_COUNT - 1;
            Difficulty_DrawChoices(tDifficulty);
            break;
        case MENUITEM_DATAMODE:
            tDataMode ^= 1;
            DataMode_DrawChoices(tDataMode);
            break;
        case MENUITEM_PERFECT_IVS:
            tPerfectIvs ^= 1;
            PerfectIvs_DrawChoices(tPerfectIvs);
            break;
        default:
            // Nothing to change on the OK row
            return;
        }
        CopyWindowToVram(WIN_OPTIONS, COPYWIN_GFX);
    }
}

static void Task_NewGameOptionsFadeOutToBirch(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_NewGameBirchSpeech_FromNewGameOptions);
    }
}

static void Task_NewGameOptionsFadeOutToMainMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        DestroyTask(taskId);
        FreeAllWindowBuffers();
        SetMainCallback2(CB2_ReinitMainMenu);
    }
}

static void HighlightNewGameOptionsItem(u8 index)
{
    SetGpuReg(REG_OFFSET_WIN0H, WIN_RANGE(16, DISPLAY_WIDTH - 16));
    SetGpuReg(REG_OFFSET_WIN0V, WIN_RANGE(index * 16 + 40, index * 16 + 56));
}

// Same as DrawOptionMenuChoice in option_menu.c: the selected choice is
// drawn in red instead of green.
static void DrawNewGameOptionsChoice(const u8 *text, u8 x, u8 y, u8 style)
{
    u8 dst[16];
    u16 i;

    for (i = 0; *text != EOS && i < ARRAY_COUNT(dst) - 1; i++)
        dst[i] = *(text++);

    if (style != 0)
    {
        dst[2] = TEXT_COLOR_RED;
        dst[5] = TEXT_COLOR_LIGHT_RED;
    }

    dst[i] = EOS;
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, dst, x, y + 1, TEXT_SKIP_DRAW, NULL);
}

static void Difficulty_DrawChoices(u8 selection)
{
    u8 styles[CHOICE_DIFFICULTY_COUNT] = {0};
    s32 widthEasy, widthMedium, xHard, xMedium;

    styles[selection] = 1;

    widthEasy = GetStringWidth(FONT_NORMAL, sText_Easy, 0);
    widthMedium = GetStringWidth(FONT_NORMAL, sText_Medium, 0);
    xHard = GetStringRightAlignXOffset(FONT_NORMAL, sText_Hard, CHOICES_RIGHT);
    // Center MEDIUM between the end of EASY and the start of HARD
    xMedium = (CHOICES_LEFT + widthEasy + xHard - widthMedium) / 2;

    DrawNewGameOptionsChoice(sText_Easy, CHOICES_LEFT, YPOS_DIFFICULTY, styles[CHOICE_EASY]);
    DrawNewGameOptionsChoice(sText_Medium, xMedium, YPOS_DIFFICULTY, styles[CHOICE_MEDIUM]);
    DrawNewGameOptionsChoice(sText_Hard, xHard, YPOS_DIFFICULTY, styles[CHOICE_HARD]);
}

static void DataMode_DrawChoices(u8 selection)
{
    u8 styles[DATA_MODE_COUNT] = {0};

    styles[selection] = 1;

    DrawNewGameOptionsChoice(sText_Vanilla, CHOICES_LEFT, YPOS_DATAMODE, styles[DATA_MODE_VANILLA]);
    DrawNewGameOptionsChoice(sText_Custom, GetStringRightAlignXOffset(FONT_NORMAL, sText_Custom, CHOICES_RIGHT), YPOS_DATAMODE, styles[DATA_MODE_CUSTOM]);
}

static void PerfectIvs_DrawChoices(u8 selection)
{
    // OFF on the left like VANILLA, ON on the right like CUSTOM
    DrawNewGameOptionsChoice(sText_Off, CHOICES_LEFT, YPOS_PERFECTIVS, selection == FALSE);
    DrawNewGameOptionsChoice(sText_On, GetStringRightAlignXOffset(FONT_NORMAL, sText_On, CHOICES_RIGHT), YPOS_PERFECTIVS, selection != FALSE);
}

static void DrawHeaderText(void)
{
    FillWindowPixelBuffer(WIN_HEADER, PIXEL_FILL(1));
    AddTextPrinterParameterized(WIN_HEADER, FONT_NORMAL, sText_GameOptions, 8, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_HEADER, COPYWIN_FULL);
}

static void DrawNewGameOptionsTexts(void)
{
    u8 i;

    FillWindowPixelBuffer(WIN_OPTIONS, PIXEL_FILL(1));
    for (i = 0; i < MENUITEM_COUNT; i++)
        AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sNewGameOptionsItemNames[i], 8, (i * 16) + 1, TEXT_SKIP_DRAW, NULL);
    AddTextPrinterParameterized(WIN_OPTIONS, FONT_NORMAL, sText_Note, 8, YPOS_NOTE + 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(WIN_OPTIONS, COPYWIN_FULL);
}

#define TILE_TOP_CORNER_L 0x1A2
#define TILE_TOP_EDGE     0x1A3
#define TILE_TOP_CORNER_R 0x1A4
#define TILE_LEFT_EDGE    0x1A5
#define TILE_RIGHT_EDGE   0x1A7
#define TILE_BOT_CORNER_L 0x1A8
#define TILE_BOT_EDGE     0x1A9
#define TILE_BOT_CORNER_R 0x1AA

#define OPTIONS_FRAME_BOTTOM (5 + OPTIONS_WIN_HEIGHT)

static void DrawBgWindowFrames(void)
{
    //                     bg, tile,              x, y, width, height, palNum
    // Draw title window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  0, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  0,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  1,  1,  2,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1,  3,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2,  3, 27,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28,  3,  1,  1,  7);

    // Draw options window frame
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_L,  1,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_EDGE,      2,  4, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_TOP_CORNER_R, 28,  4,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_LEFT_EDGE,     1,  5,  1, OPTIONS_WIN_HEIGHT,  7);
    FillBgTilemapBufferRect(1, TILE_RIGHT_EDGE,   28,  5,  1, OPTIONS_WIN_HEIGHT,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_L,  1, OPTIONS_FRAME_BOTTOM,  1,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_EDGE,      2, OPTIONS_FRAME_BOTTOM, 26,  1,  7);
    FillBgTilemapBufferRect(1, TILE_BOT_CORNER_R, 28, OPTIONS_FRAME_BOTTOM,  1,  1,  7);

    CopyBgTilemapBufferToVram(1);
}
