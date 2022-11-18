package com.example.java;

public enum Instruments {
    PIANO((byte)0),
    FLUTE((byte)75),
    ELECTRIC_GUITAR((byte)27),
    TRUMPET((byte)56),
    BASS((byte)33);


    Instruments(byte value){
        this.value=value;
    }

    @Override
    public String toString() {
        return String.valueOf(value);
    }

    private final byte value;
}
