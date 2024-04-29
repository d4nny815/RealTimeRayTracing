import sys
from PIL import Image

DISP_WIDTH = 256
DISP_HEIGHT = 192
# DISP_WIDTH = 512
# DISP_HEIGHT = 384



def main():
    filename = sys.argv[1]
    img = Image.open(filename)
    new_img = img.resize((DISP_WIDTH, DISP_HEIGHT))
    new_img.convert('RGB')
    # new_img.save('frame.png')
    
    with open('start_frame.mem', 'w') as f:
        for h in range(DISP_WIDTH):
            for v in range(DISP_WIDTH):
                if v > DISP_HEIGHT - 1:
                    f.write('0\n')
                    continue
                r, g, b, o = 0, 0, 0, 0
                try:
                    r, g, b, o = new_img.getpixel((h, v))
                except:
                    r, g, b = new_img.getpixel((h, v))
                    
                r = r >> 4
                g = g >> 4
                b = b >> 4
                if (r > 0xf or g > 0xf or b > 0xf):
                    print(f'Pixel at {h}, {v} is not 4-bit color ({r}, {g}, {b})')

                f.write(f'{r:01x}{g:01x}{b:01x}\n')

if __name__ == '__main__':
    main()