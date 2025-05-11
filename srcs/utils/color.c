unsigned int cub_rgb_to_int(double r, double g, double b)
{
    unsigned int color;

    color |= (unsigned int)(b * 255);
    color |= (unsigned int)(g * 255) << 8;
    color |= (unsigned int)(r * 255) << 16;
    return (color);
}