int rgb_to_int(double r, double g, double b)
{
    int color;

    color |= (int)(b * 255);
    color |= (int)(g * 255) << 8;
    color |= (int)(r * 255) << 16;
    return (color);
}