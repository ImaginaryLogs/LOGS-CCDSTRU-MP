
#define MAXSIZE 72
#define BG_BLACK (0x0)
typedef char String15[16];
typedef int coord[2];

// A general struct for a set of 1D
struct set1D {
    coord D1Array[MAXSIZE];
    int length;
    int maxSize;
};

// A general struct for a set of 2D
struct set2D {
    struct set1D D2Array[MAXSIZE];
    int width;
    int maxSize;
};

// A general struct for a set of 3D
struct set3D {
    struct set2D D3Array[MAXSIZE];
    int height;
    int maxSize;
};
