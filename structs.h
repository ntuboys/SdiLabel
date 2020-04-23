#ifndef STRUCTS_H
#define STRUCTS_H

#include <QString>

typedef struct label {
    int labelId;
    int imageId;
    QString className;
    int x;
    int y;
    int width;
    int height;
    bool occluded;
} label;

typedef struct image {
    int imageId;
    QString path;
} image;

#endif // STRUCTS_H
