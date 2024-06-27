/**Solutions to Chapter 2, Section 2, Exercise 1 of Horowitz's Data Structures.
 */

#include <stdio.h>
#include <string.h>

typedef struct solarSys {
    char planetName[10];
    int solarDist;
    int ownSatellite;
} solarSystem;

int main() {
    solarSystem earth, venus;

    strcpy(earth.planetName, "Earth");
    earth.solarDist = 14960;
    earth.ownSatellite = 1;
    printf("%s\n", earth.planetName);
    printf("%d\n", earth.solarDist);
    printf("%d\n", earth.ownSatellite);
    printf("\n");

    strcpy(venus.planetName, "Venus");
    venus.solarDist = 10750;
    venus.ownSatellite = 0;
    printf("%s\n", venus.planetName);
    printf("%d\n", venus.solarDist);
    printf("%d\n", venus.ownSatellite);
    printf("\n");

    return 0;
}
