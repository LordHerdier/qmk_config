#ifndef RUN_CMDS_H
#define RUN_CMDS_H

#include "custom_keycodes.h"

/**
 * @brief Array of commands to be used with QMK keybindings to quickly run commands.
 *
 * This array is used in conjunction with the `run_cmd()` function in QMK keybindings
 * to quickly run commands. Each element in the array represents a command to be executed.
 * The index of each element is calculated based on the corresponding command's position
 * relative to `RUN_CMD_START` constant.
 *
 * @note Make sure to update the array elements if you want to add or modify the commands.
 */
static const char *run_cmds[] = {
    [RUN_WT   - RUN_CMD_START] = "wt.exe",
    [RUN_BROWSER - RUN_CMD_START] = "zen.exe",
    [RUN_NOTEPAD - RUN_CMD_START] = "notepad.exe",
    [RUN_FILES - RUN_CMD_START] = "explorer.exe",
};

// run command helper function
/**
 * Executes a command in the Windows "Run" dialog.
 *
 * @param cmd The command to be executed.
 */
static void run_cmd(const char *cmd) {
    // pop open the Windows “Run” dialog
    SEND_STRING(SS_LGUI("r"));
    wait_ms(150);
    // type the actual command, then Enter
    SEND_STRING(cmd);
    tap_code(KC_ENT);
}

// generic “run” handler
bool process_run_cmd(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed
        && keycode >= RUN_CMD_START
        && keycode < RUN_CMD_END) {
        run_cmd(run_cmds[keycode - RUN_CMD_START]);
        return false;
    }
    return true;
}


#endif // RUN_CMDS_H