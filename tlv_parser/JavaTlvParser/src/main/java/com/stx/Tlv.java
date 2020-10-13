// This is a generated file! Please edit source .ksy file and use kaitai-struct-compiler to rebuild

package com.stx;

import io.kaitai.struct.ByteBufferKaitaiStream;
import io.kaitai.struct.KaitaiStruct;
import io.kaitai.struct.KaitaiStream;
import java.io.IOException;
import java.nio.charset.Charset;

public class Tlv extends KaitaiStruct {
    public static Tlv fromFile(String fileName) throws IOException {
        return new Tlv(new ByteBufferKaitaiStream(fileName));
    }

    public Tlv(KaitaiStream _io) {
        this(_io, null, null);
    }

    public Tlv(KaitaiStream _io, KaitaiStruct _parent) {
        this(_io, _parent, null);
    }

    public Tlv(KaitaiStream _io, KaitaiStruct _parent, Tlv _root) {
        super(_io);
        this._parent = _parent;
        this._root = _root == null ? this : _root;
        _read();
    }
    private void _read() {
        this.idTag = this._io.readU4be();
        this.lenTag = this._io.readU4be();
        this.bodyTag = new String(this._io.readBytes(lenTag()), Charset.forName("ASCII"));
    }
    private long idTag;
    private long lenTag;
    private String bodyTag;
    private Tlv _root;
    private KaitaiStruct _parent;
    public long idTag() { return idTag; }
    public long lenTag() { return lenTag; }
    public String bodyTag() { return bodyTag; }
    public Tlv _root() { return _root; }
    public KaitaiStruct _parent() { return _parent; }
}
