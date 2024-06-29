#ifndef game_misc_hpp
#define game_misc_hpp

#define SLAUGHTERHOUSE_FLOOR_TILE_OFFSET 107, 39
#define SLAUGHTERHOUSE_BLADE_OFFSET 1482, 2986
#define GENERATE_OBSTACLES_RECIPE rand() % 5;

namespace GameConstants {
inline const char *title{"GRA W KRUWSKO"};
inline const uint32_t width = 1366;
inline const uint32_t height = 768;

// Player - related constants
inline const uint32_t playerFrameH = 512;
inline const uint32_t playerFrameW = 720;
inline const uint32_t playerEntityH = 128;
inline const uint32_t playerEntityW = 180;

// Slaughterhouse flooring - related constants
inline const uint32_t floorFrameSquare = 860;
inline const uint32_t floorEntitySquare = 86;

// Slaughterhouse blades - related constants
inline const uint32_t bladeFrameSquare = 1000;
inline const uint32_t bladeEntitySquare = 250;
inline const uint32_t maxBladeHorizontalThreshold =
    GameConstants::width - GameConstants::bladeEntitySquare;
inline const uint32_t maxBladeVerticalThreshold =
    GameConstants::height - GameConstants::bladeEntitySquare;
inline const int32_t bladeEntityLeftThreshold =
    GameConstants::bladeEntitySquare * -1;

// Animation - related stuff
inline const uint32_t maxTimeBetweenAnimationRefresh = 100u;
inline const uint32_t minTimeBetweenAnimationRefresh = 1u;
inline const uint32_t animationFreqStep = 16u;
inline const int32_t floorEntityLeftThreshold =
    GameConstants::floorEntitySquare * -1;
inline const uint32_t floorAnimationTicks = 10u;

// Physics - related stuff
inline const double playerAcceleration = 5u;
}

#endif