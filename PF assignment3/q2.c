#include <stdio.h>

// Recursive function to simulate spacecraft fuel journey
void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    // Base case: fuel exhausted or all planets visited
    if (fuel <= 0)
    {
        printf("Planet %d: Fuel Remaining = 0 (Mission Failed)\n", planet);
        return;
    }
    if (planet > totalPlanets)
    {
        printf("Mission Successful! Spacecraft completed the journey.\n");
        return;
    }

    // Fuel adjustments for this planet
    fuel -= consumption; // consume fuel
    fuel += recharge;    // gravitational assist recharge

    // Solar recharge every 4th planet
    if (planet % 4 == 0)
    {
        fuel += solarBonus;
    }

    // Print current status
    if (fuel > 0)
        printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    else
    {
        printf("Planet %d: Fuel Remaining = 0 (Mission Failed)\n", planet);
        return; // stop recursion if fuel exhausted
    }

    // Recursive call for next planet
    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main()
{
    int initialFuel, consumption, recharge, solarBonus, totalPlanets;

    // Example input
    // Initial fuel = 100, consumption = 20, recharge = 5, solarBonus = 30, totalPlanets = 6
    scanf("%d %d %d %d %d", &initialFuel, &consumption, &recharge, &solarBonus, &totalPlanets);

    // Start journey from planet 1
    calculateFuel(initialFuel, consumption, recharge, solarBonus, 1, totalPlanets);

    return 0;
}