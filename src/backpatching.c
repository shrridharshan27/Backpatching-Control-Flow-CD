/**
 * ============================================================================
 * Course: Compiler Design Laboratory (BCSE306L)
 * Experiment 11: Backpatching for Control Flow & Boolean Expressions
 * Author: Shrri Dharshan D R (Reg No: 23BPS1090)
 * Slot: L23+L24
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTR 32

typedef struct {
    int index;
    char text[64];
    int patched_target;
} Instruction;

Instruction code[MAX_INSTR];
int next_instr = 1;

/* Emit instruction with placeholder jump */
int emit_jump(const char *cond) {
    int idx = next_instr++;
    code[idx].index = idx;
    if (cond) {
        snprintf(code[idx].text, sizeof(code[idx].text), "if %s goto _", cond);
    } else {
        snprintf(code[idx].text, sizeof(code[idx].text), "goto _");
    }
    code[idx].patched_target = -1;
    return idx;
}

void emit_action(const char *action) {
    int idx = next_instr++;
    code[idx].index = idx;
    snprintf(code[idx].text, sizeof(code[idx].text), "%s", action);
    code[idx].patched_target = -1;
}

void backpatch(int instr_idx, int target) {
    code[instr_idx].patched_target = target;
    char *p = strstr(code[instr_idx].text, "_");
    if (p) {
        snprintf(p, 16, "%d", target);
    }
}

int main(void) {
    printf("============================================================\n");
    printf("     EXPERIMENT 11: BACKPATCHING IN THREE ADDRESS CODE      \n");
    printf("============================================================\n\n");

    printf("Translating Source Construct:\n");
    printf("  if (a < b)\n");
    printf("      x = y + z;\n");
    printf("  else\n");
    printf("      x = y - z;\n\n");

    /* Phase 1: Generate Intermediate Code with pending lists */
    int true_list = emit_jump("a < b");     // Instruction 1: if a < b goto _
    int false_list = emit_jump(NULL);       // Instruction 2: goto _

    int then_start = next_instr;            // Target for true_list (4)
    emit_action("x = y + z");               // Instruction 3 / 4
    int next_list = emit_jump(NULL);        // Instruction 5: goto _

    int else_start = next_instr;            // Target for false_list (6)
    emit_action("x = y - z");               // Instruction 6

    int next_start = next_instr;            // Target for next_list (7)
    emit_action("next_instruction");        // Instruction 7

    printf("Intermediate Code (BEFORE Backpatching):\n");
    printf("------------------------------------------------------------\n");
    printf("  1: if a < b goto _   [TrueList  -> pending]\n");
    printf("  2: goto _            [FalseList -> pending]\n");
    printf("  3: x = y + z\n");
    printf("  4: goto _            [NextList  -> pending]\n");
    printf("  5: x = y - z\n");
    printf("  6: next_instruction\n\n");

    /* Phase 2: Apply Backpatching resolutions */
    backpatch(true_list, then_start);
    backpatch(false_list, else_start);
    backpatch(next_list, next_start);

    printf("Backpatching Execution Trace:\n");
    printf("------------------------------------------------------------\n");
    printf("  Instruction %d (TrueList)  patched with target address -> %d\n", true_list, then_start);
    printf("  Instruction %d (FalseList) patched with target address -> %d\n", false_list, else_start);
    printf("  Instruction %d (NextList)  patched with target address -> %d\n\n", next_list, next_start);

    printf("Final Generated Three Address Code (AFTER Backpatching):\n");
    printf("============================================================\n");
    for (int i = 1; i < next_instr; i++) {
        printf("  %d: %s\n", code[i].index, code[i].text);
    }
    printf("============================================================\n");

    return 0;
}
