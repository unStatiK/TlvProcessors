meta:
  id: tlv
  file-extension: data
  endian: be
seq:
  - id: id_tag
    type: u4
  - id: len_tag
    type: u4
  - id: body_tag
    type: str
    size: len_tag
    encoding: ASCII