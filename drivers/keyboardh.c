#pragma once
#include "disp.h"
#include "../isr.h"


void print_letter(uint8_t scancode) {
    switch (scancode) {
        case 0x0:
            print_s("ERROR");
            break;
        case 0x1:
            print_s("ESC");
            break;
        case 0x2:
            print_s("1");
            break;
        case 0x3:
            print_s("2");
            break;
        case 0x4:
            print_s("3");
            break;
        case 0x5:
            print_s("4");
            break;
        case 0x6:
            print_s("5");
            break;
        case 0x7:
            print_s("6");
            break;
        case 0x8:
            print_s("7");
            break;
        case 0x9:
            print_s("8");
            break;
        case 0x0A:
            print_s("9");
            break;
        case 0x0B:
            print_s("0");
            break;
        case 0x0C:
            print_s("-");
            break;
        case 0x0D:
            print_s("+");
            break;
        case 0x0E:
            print_s("Backspace");
            break;
        case 0x0F:
            print_s("Tab");
            break;
        case 0x10:
            print_s("Q");
            break;
        case 0x11:
            print_s("W");
            break;
        case 0x12:
            print_s("E");
            break;
        case 0x13:
            print_s("R");
            break;
        case 0x14:
            print_s("T");
            break;
        case 0x15:
            print_s("Y");
            break;
        case 0x16:
            print_s("U");
            break;
        case 0x17:
            print_s("I");
            break;
        case 0x18:
            print_s("O");
            break;
        case 0x19:
            print_s("P");
            break;
        case 0x1A:
            print_s("[");
            break;
        case 0x1B:
            print_s("]");
            break;
        case 0x1C:
            print_s("ENTER");
            break;
        case 0x1D:
            print_s("LCtrl");
            break;
        case 0x1E:
            print_s("A");
            break;
        case 0x1F:
            print_s("S");
            break;
        case 0x20:
            print_s("D");
            break;
        case 0x21:
            print_s("F");
            break;
        case 0x22:
            print_s("G");
            break;
        case 0x23:
            print_s("H");
            break;
        case 0x24:
            print_s("J");
            break;
        case 0x25:
            print_s("K");
            break;
        case 0x26:
            print_s("L");
            break;
        case 0x27:
            print_s(";");
            break;
        case 0x28:
            print_s("'");
            break;
        case 0x29:
            print_s("`");
            break;
        case 0x2A:
            print_s("LShift");
            break;
        case 0x2B:
            print_s("\\");
            break;
        case 0x2C:
            print_s("Z");
            break;
        case 0x2D:
            print_s("X");
            break;
        case 0x2E:
            print_s("C");
            break;
        case 0x2F:
            print_s("V");
            break;
        case 0x30:
            print_s("B");
            break;
        case 0x31:
            print_s("N");
            break;
        case 0x32:
            print_s("M");
            break;
        case 0x33:
            print_s(",");
            break;
        case 0x34:
            print_s(".");
            break;
        case 0x35:
            print_s("/");
            break;
        case 0x36:
            print_s("Rshift");
            break;
        case 0x37:
            print_s("Keypad *");
            break;
        case 0x38:
            print_s("LAlt");
            break;
        case 0x39:
            print_s("Space");
            break;
        default:
            /* 'keuyp' event corresponds to the 'keydown' + 0x80
             * it may still be a scancode we haven't implemented yet, or
             * maybe a control/escape sequence */
            if (scancode <= 0x7f) {
                print_s("Unknown key down");
            } else if (scancode <= 0x39 + 0x80) {
                print_s("key up ");
                print_letter(scancode - 0x80);
            } else print_s("Unknown key up");
            break;
    }
}

static void keyboard_call(registers_t *rgs){
    uint8_t scancode = port_byte_in(0x60);
    print_letter(scancode);
    nl();
}
void init_keyboard(){
    register_interrupt_handler(IRQ1,keyboard_call);

}

