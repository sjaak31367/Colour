#pragma once

// 1: print RGB combined
// 2: print 3D stuff
// 3: print 3D planet (v1)
#define PRINTMODE 3

// Terminal Window size in chars devided by 2
//                                 Home : School
#define TERMINALSIZEX 105 //        105 : 50
#define TERMINALSIZEY 50 //          50 : 61



#if PRINTMODE == 2 || PRINTMODE == 3
#define STORAGESIZEX TERMINALSIZEX
#define STORAGESIZEY TERMINALSIZEY
#endif // PRINTMODE == 2 || PRINTMODE == 3

#if PRINTMODE == 3
#define WATERLEVEL 128
#define STORAGESIZEZ (static_cast<int>(std::ceil(radius))+3)
#endif // PRINTMODE == 3

#if PRINTMODE == 2
#define STORAGESIZEZ 100
#endif // PRINTMODE == 2
