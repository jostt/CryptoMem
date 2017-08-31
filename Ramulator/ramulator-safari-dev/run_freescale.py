from subprocess import call
import sys

single_threaded =[
                "trace1-inflight-5",
                "trace1-inflight-10",
                "trace1-inflight-20",
                "trace1-inflight-50",
                "trace4-inflight-5",
                "trace4-inflight-10",
                "trace4-inflight-20",
                "trace4-inflight-50",
                ]

DRAM_list = [
  "DDR3-2133L", "DDR4-2400R", "LPDDR3-2133", "LPDDR4-3200", "GDDR5-7000", "WideIO-266", "WideIO2-1067", "HBM-1000", "HMC", "HMC-RoBaCoVa"
]

ramulator_bin = "/Users/tianshi/backup-lol/tianshi-Workspace/ramulator/ramulator"

if not len(sys.argv) == 4:
  print "python run_freescale.py trace_dir output_dir config_dir"
  sys.exit(0)

config_dir = sys.argv[3]
output_dir = sys.argv[2]
trace_dir = sys.argv[1]

for workload_id in range(len(single_threaded)):
  output_dir = sys.argv[2] + "/" + single_threaded[workload_id]
  print output_dir
  call(["mkdir", "-p", output_dir])

  l = single_threaded[workload_id].split("-")
  trace_name = l[0]
  trace = trace_dir + "/" + trace_name + ".trace"
  inflight_limit = l[2]

  for DRAM in DRAM_list:
    output = output_dir + "/" + DRAM + ".stats"
    config = config_dir + "/" + DRAM + "-config.cfg"
    chan = 2
    rank = 2
    if DRAM == "GDDR5-7000":
      chan = 2
      rank = 1
    elif DRAM == "WideIO-266":
      chan = 4
      rank = 1
    elif DRAM == "WideIO2-1067":
      chan = 4
      rank = 2
    if "HMC" in DRAM:
      cmds = [ramulator_bin, "--mode", "dram", "--config", config, "--cache", "no", "--trace", trace, "--inflight-limit", inflight_limit, "--translation", "None", "--org", "HMC_8GB", "--stats", output]
    elif "HBM" in DRAM:
      cmds = [ramulator_bin, "--mode", "dram", "--config", config, "--cache", "no", "--trace", trace, "--inflight-limit", inflight_limit, "--translation", "None", "--stats", output]
    else:
      cmds = [ramulator_bin, "--mode", "dram", "--config", config, "--cache", "no", "--trace", trace, "--inflight-limit", inflight_limit, "--channel", str(chan), "--rank", str(rank), "--translation", "None", "--stats", output]

    print(" ".join(cmds))
    call(cmds)

