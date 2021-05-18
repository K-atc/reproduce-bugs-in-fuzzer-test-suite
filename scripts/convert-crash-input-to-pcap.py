"""usage
python3 scripts/convert-crash-input-to-pcap.py
"""
from scapy.all import *
import argparse

parser = argparse.ArgumentParser(description='Convert crash input to pcap format')
parser.add_argument("crash_input")
parser.add_argument("pcap_file")
args = parser.parse_args()

with open(args.crash_input, "rb") as f:
    data = f.read()
    pkt = Ether()/IP()/TCP(dport=443)/Raw(data)
    wrpcap(args.pcap_file, [pkt])