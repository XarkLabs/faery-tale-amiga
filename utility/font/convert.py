import json
from PIL import Image


def convert_font_data(name):
    print("Converting %s..." % name)
    with open("%s.json" % name) as file:
        data = json.load(file)

    out = open("%s.fnt" % name, "wb")
    
    y_size = data['ySize']
    lo_char = data['loChar']
    hi_char = data['hiChar']
    nb_chars = hi_char - lo_char + 1

    out.write(lo_char.to_bytes(1, "little"))
    out.write(nb_chars.to_bytes(1, "little"))

    total_width = 0
    for i in range(nb_chars):
        glyph = data['glyphs'][str(i + lo_char)]
        total_width += glyph['bitLength']

    im = Image.new(mode="RGBA", size=(total_width, y_size))
    
    x = 0
    y = 0
    for i in range(nb_chars):
        glyph = data['glyphs'][str(i + lo_char)]
        bitmap = glyph['bitmap']
        yy = 0
        for line in bitmap:
            xx = 0
            for p in line:
                v = (0, 0, 0, 0)
                if p == 1:
                    v = (255, 255, 255, 255)
                im.putpixel((x + xx, y + yy), v)
                xx += 1
            yy += 1
        location_start = glyph['locationStart']
        bit_length = glyph['bitLength']
        spacing = bit_length
        if 'spacing' in glyph.keys():
            spacing = glyph['spacing']
        out.write(location_start.to_bytes(2, "little"))
        out.write(bit_length.to_bytes(1, "little"))
        out.write(spacing.to_bytes(1, "little"))
        x += bit_length

    im.save("%s.png" % name)
    out.close()


def convert_font(name):
    with open("%s.json" % name) as file:
        data = json.load(file)

    for entry_key in data['entries']:
        entry = data['entries'][entry_key]
        convert_font_data("%s_%s" % (entry['fontName'], entry['pointSize']))


convert_font('topaz')
convert_font('amber')
