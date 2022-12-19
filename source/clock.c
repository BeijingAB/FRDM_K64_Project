#include "clock.h"

// Set external clock 50 MHz from EXTAL 0
void clock_init()
{
	// 50M external [105170 - 105190 baud rate, sbr=1f] =>
	// OSC0 -> OSCSELCLK
	MCG->C7 |= MCG_C7_OSCSEL(0);

	// OSCSELCLK -> MCGOUTCLK
	MCG->C1 |= MCG_C1_CLKS(2);

/* Clock settings default [105170 - 105190 baud rate]
 * System clokc <- [SIM_CLKDIV1 (OUTDIV1 = 0) /1] <- MCGOUTCLK <- [MCG_C1 (CLKS = 0) Output of PLL/FLL]
 * <- [MCG_C6 (PLLS = 0) FLL selected] <- DCOOUT <- [MCG_C4 (DMX32 = 0, DRST_DRS = 0),
 * Ref Range = 31.25-2 ~ 39.0625 kHz, FLL Factor = 640, DCO Range = 20 ~ 25 MHz] <- [MCG_C1 (IREFS = 1)
 * Slow internal Ref clk] <- Slow Clock <-
 *
 *
 * */
}
