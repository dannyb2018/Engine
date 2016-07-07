#!/usr/bin/env python

import os
import runpy
ore_helpers = runpy.run_path(os.path.join(os.path.dirname(os.getcwd()), "ore_examples_helper.py"))
OreExample = ore_helpers['OreExample']

import sys
oreex = OreExample(sys.argv[1] if len(sys.argv)>1 else False)

oreex.print_headline("Run ORE to produce NPV cube and exposures")
oreex.run("Input/ore.xml")
oreex.get_times("Output/log.txt")

oreex.print_headline("Run ORE to price European Payer Swaptions")
oreex.run("Input/ore_payer_swaption.xml")

oreex.print_headline("Run ORE to price European Receiver Swaptions")
oreex.run("Input/ore_receiver_swaption.xml")

oreex.print_headline("Plot results: Simulated exposures vs analytical Swaption prices")

oreex.setup_plot("swaps_swaptions")
oreex.plot("exposure_trade_Swap_20.csv", 2, 3, 'b', "EPE")
oreex.plot("exposure_trade_Swap_20.csv", 2, 4, 'r', "ENE")
oreex.plot_npv("npv_payer.csv", 6, 'g', 'Payer Swaption')
oreex.plot_npv("npv_receiver.csv", 6, 'm', 'Receiver Swaption')
oreex.decorate_plot(title="Example 3")
oreex.save_plot_to_file()

