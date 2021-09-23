#include "shape.h" /* Shape class interface */

/* constructor implementation */
typedef struct Shape{
 int16_t x; /* x-coordinate of Shape's position */
 int16_t y; /* y-coordinate of Shape's position */
} Shape;

void Shape_ctor(Shape * const me, int16_t x, int16_t y) {
 me->x = x;
 me->y = y;
}
/* move-by operation implementation */
void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy) {
 me->x += dx;
 me->y += dy;
}
/* "getter" operations implementation */
int16_t Shape_getX(Shape * const me) {
 return me->x;
}
int16_t Shape_getY(Shape * const me) {
 return me->y;
}

int shapeSize() {
    return sizeof(Shape);
}

