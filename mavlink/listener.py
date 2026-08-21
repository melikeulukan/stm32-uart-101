"""Simple serial listener for the custom MAVLink dialect.

Reads raw bytes from a serial port, decodes them as MAVLink v2 frames using
the project's custom dialect (mavlink/dialects/custom.xml), and prints each
decoded MISSION_TELEMETRY message.

Usage:
    python listener.py <COM_PORT> [BAUD]

Example:
    python listener.py COM5 115200
"""
import os
import sys

# Must be set before mavutil picks the dialect, so it loads
# pymavlink.dialects.v20.custom instead of the v1.0 folder.
os.environ["MAVLINK20"] = "1"

from pymavlink import mavutil


def main():
    if len(sys.argv) < 2:
        print("Kullanim: python listener.py <COM_PORT> [BAUD]")
        print("Ornek:    python listener.py COM5 115200")
        sys.exit(1)

    port = sys.argv[1]
    baud = int(sys.argv[2]) if len(sys.argv) > 2 else 115200

    mav = mavutil.mavlink_connection(port, baud=baud, dialect="custom")

    print(f"{port} @ {baud} baud dinleniyor (Ctrl+C ile cikis)...")

    while True:
        msg = mav.recv_match(blocking=True, timeout=5)
        if msg is None:
            print("... 5 saniyedir mesaj gelmedi ...")
            continue
        print(msg)


if __name__ == "__main__":
    main()
