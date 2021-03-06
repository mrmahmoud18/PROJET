#pragma once

enum ActionType
{
    ADD,
    ADD_BUFF,			//Add 1-input Buffer gate
    ADD_INV,			//Add 1-input Inverter gate
    ADD_AND_GATE_2,		//Add 2-input AND gate
    ADD_NAND_GATE_2,	//Add 2-input NAND gate
    ADD_OR_GATE_2,		//Add 2-input OR gate
    ADD_NOR_GATE_2,		//Add 2-input NOR gate
    ADD_XOR_GATE_2,		//Add 2-input XOR gate
    ADD_XNOR_GATE_2,	//Add 2-input XNOR gate
    ADD_AND_GATE_3,		//Add 3-input AND gate
    ADD_NAND_GATE_3,	//Add 3-input NAND gate
    ADD_OR_GATE_3,		//Add 3-input OR gate
    ADD_NOR_GATE_3,		//Add 3-input NOR gate
    ADD_XOR_GATE_3,		//Add 3-input XOR gate
    ADD_XNOR_GATE_3,	//Add 3-input XNOR gate
    ADD_SWITCH,			//Add Switch
    ADD_LED,			//Add LED

    ADD_CONNECTION,		//Add Wire Connection

    ADD_LABEL,			//Add Label to a Component, a Connection
    EDIT_LABEL,			//Edit Label of a Component, a Connection

    CREATE_TRUTHTABLE,	//Create Truth Table of the Circuit

    ACTIVE_BAR_CLICK,
    CANVAS_LEFT_CLICK,
    CANVAS_RIGHT_CLICK,

    MULTI_SELECT,

    DELETE,                //Delete a Component, a Connection
    DRAG,		        //Move a Component

    COPY,               //Copy a Component
    CUT,                //Cut a Component
    PASTE,              //Paste a Component

    SAVE,		        //Save the whole Circuit to a file
    LOAD,		        //Load a Circuit from a file

    UNDO,		        //Undo the last Action preformed
    REDO,		        //Redo the last Action canceled

    SWITCH_MODE,        //Switch Application Mode
    SWITCH_THEME,       //Switch Application Theme
    ADJUST_OFFSET,
    ZOOM_IN,
    ZOOM_OUT,

    EXIT,               //Exit the application

    STATUS_BAR,		    //A click on the status bar

    NONE

};

enum ComponentStatus
{
    NORMAL,
    SELECTED,
    INVALID
};

enum Signal
{
    LOW,
    HIGH,
    FLOATING
};
