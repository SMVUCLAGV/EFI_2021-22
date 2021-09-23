#ifndef SHAPE_H
#define SHAPE_H
/* Shape's attributes... */
#include <stdint.h>

typedef struct Shape Shape;

/* Shape's operations (Shape's interface)... */
void Shape_ctor(Shape * const me, int16_t x, int16_t y);
void Shape_moveBy(Shape * const me, int16_t dx, int16_t dy);
int16_t Shape_getX(Shape * const me);
int16_t Shape_getY(Shape * const me);
int shapeSize();
#endif /* SHAPE_H */
