package com.stx;

import java.io.IOException;

public class Main {

    private static final String inputFileName = "tlv.data";

    public static void main(String[] args) throws IOException {
        readFile(inputFileName);
    }

    private static void readFile(String fileName) throws IOException {
        Tlv tlv = Tlv.fromFile(fileName);
        boolean isLast = false;
        do {
            System.out.println("=========================================");
            System.out.println(String.format("id:\t\t [%s]", tlv.idTag()));
            System.out.println(String.format("len:\t [%s]", tlv.lenTag()));
            System.out.println(String.format("body:\t [%s]", tlv.bodyTag()));
            isLast = tlv._io().isEof();
            if (!isLast) {
                tlv = new Tlv(tlv._io());
            }
        } while (!isLast);
    }
}
