Step 1: Begin Simulator Initialization...
node: 1
node: 2
node: 3
node: 4
link: 1 2 10 0.000000
link: 2 4 59 0.000000
link: 1 3 10 0.000000
link: 3 4 10 0.000000
Reading events...
Line being read is: 0.01   xmit (2,4)
Line being read is: 11.00  xmit (2,4)
Line being read is: 40.00 xmit (2,4)
Line being read is: 45.00 linkdying (3,4)
Line being read is: 70.00 xmit (2,4)
Line being read is: 71.00 xmit (4,2)
Line being read is: 80.00 linkcomingup (3,4)
Line being read is: 95.00 xmit (2,4)
Line being read is: 100.00 end
Simulator Initialization complete.
Step 2: Simulator beginning to run...
time = 0.01 Event_Xmit_Data_Pkt source node 2 destination node 4 packet type is DATA
	Packet generated locally, destination: 4.
	Cannot forward the packet (not reachable).
time = 0.9 Event_Alarm on node 2
time = 0.9 Event_Alarm on node 3
time = 0.9 Event_Alarm on node 0
time = 0.9 Event_Alarm on node 0
time = 1.8 Event_Alarm on node 2
time = 1.8 Event_Alarm on node 3
time = 1.8 Event_Alarm on node 0
time = 1.8 Event_Alarm on node 0
time = 2.7 Event_Alarm on node 2
time = 2.7 Event_Alarm on node 3
time = 2.7 Event_Alarm on node 0
time = 2.7 Event_Alarm on node 0
time = 3.6 Event_Alarm on node 2
time = 3.6 Event_Alarm on node 3
time = 3.6 Event_Alarm on node 0
time = 3.6 Event_Alarm on node 0
time = 4.5 Event_Alarm on node 2
time = 4.5 Event_Alarm on node 3
time = 4.5 Event_Alarm on node 0
time = 4.5 Event_Alarm on node 0
time = 5.4 Event_Alarm on node 2
time = 5.4 Event_Alarm on node 3
time = 5.4 Event_Alarm on node 0
time = 5.4 Event_Alarm on node 0
time = 6.3 Event_Alarm on node 2
time = 6.3 Event_Alarm on node 3
time = 6.3 Event_Alarm on node 0
time = 6.3 Event_Alarm on node 0
time = 7.2 Event_Alarm on node 2
time = 7.2 Event_Alarm on node 3
time = 7.2 Event_Alarm on node 0
time = 7.2 Event_Alarm on node 0
time = 8.1 Event_Alarm on node 2
time = 8.1 Event_Alarm on node 3
time = 8.1 Event_Alarm on node 0
time = 8.1 Event_Alarm on node 0
time = 9 Event_Alarm on node 2
time = 9 Event_Alarm on node 3
time = 9 Event_Alarm on node 0
time = 9 Event_Alarm on node 0
time = 9.9 Event_Alarm on node 2
time = 9.9 Event_Alarm on node 3
time = 9.9 Event_Alarm on node 0
time = 9.9 Event_Alarm on node 0
time = 10 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 10000
	Send PING to port: 0, time stamp: 10000
time = 10 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 10000
	Send PING to port: 0, time stamp: 10000
time = 10 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 10 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 10 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 10 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 10 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 10000
	Send PING to port: 0, time stamp: 10000
time = 10 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 10 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 10 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 10000
	Send PING to port: 0, time stamp: 10000
time = 10 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 10 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 10.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 10000
time = 10.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 10000
time = 10.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 10.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 10.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 10000
time = 10.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 10000
time = 10.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 10.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 10.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 10000
time = 10.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 10000
time = 10.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 10.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 10.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 10020
time = 10.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 10020
time = 10.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 10020
time = 10.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 10020
time = 10.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 10020
time = 10.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 10020
time = 10.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 10000
time = 10.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 10000
time = 10.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 10.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 10.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 10118
time = 10.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 10118
time = 10.8 Event_Alarm on node 2
time = 10.8 Event_Alarm on node 3
time = 10.8 Event_Alarm on node 0
time = 10.8 Event_Alarm on node 0
time = 11 Event_Xmit_Data_Pkt source node 2 destination node 4 packet type is DATA
	Packet generated locally, destination: 4.
	Forward the packet through port 1.
time = 11 Event_Xmit_Pkt_On_Link (2,4) packet type is DATA
time = 11.059 Event_Recv_Pkt_On_Node 4 packet type is DATA
	Receive data from 2, No payload in the message.
time = 11.7 Event_Alarm on node 2
time = 11.7 Event_Alarm on node 3
time = 11.7 Event_Alarm on node 0
time = 11.7 Event_Alarm on node 0
time = 12.6 Event_Alarm on node 2
time = 12.6 Event_Alarm on node 3
time = 12.6 Event_Alarm on node 0
time = 12.6 Event_Alarm on node 0
time = 13.5 Event_Alarm on node 2
time = 13.5 Event_Alarm on node 3
time = 13.5 Event_Alarm on node 0
time = 13.5 Event_Alarm on node 0
time = 14.4 Event_Alarm on node 2
time = 14.4 Event_Alarm on node 3
time = 14.4 Event_Alarm on node 0
time = 14.4 Event_Alarm on node 0
time = 15.3 Event_Alarm on node 2
time = 15.3 Event_Alarm on node 3
time = 15.3 Event_Alarm on node 0
time = 15.3 Event_Alarm on node 0
time = 16.2 Event_Alarm on node 2
time = 16.2 Event_Alarm on node 3
time = 16.2 Event_Alarm on node 0
time = 16.2 Event_Alarm on node 0
time = 17.1 Event_Alarm on node 2
time = 17.1 Event_Alarm on node 3
time = 17.1 Event_Alarm on node 0
time = 17.1 Event_Alarm on node 0
time = 18 Event_Alarm on node 2
time = 18 Event_Alarm on node 3
time = 18 Event_Alarm on node 0
time = 18 Event_Alarm on node 0
time = 18.9 Event_Alarm on node 2
time = 18.9 Event_Alarm on node 3
time = 18.9 Event_Alarm on node 0
time = 18.9 Event_Alarm on node 0
time = 19.8 Event_Alarm on node 2
time = 19.8 Event_Alarm on node 3
time = 19.8 Event_Alarm on node 0
time = 19.8 Event_Alarm on node 0
time = 20 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 20000
	Send PING to port: 0, time stamp: 20000
time = 20 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 20000
	Send PING to port: 0, time stamp: 20000
time = 20 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 20000
	Send PING to port: 0, time stamp: 20000
time = 20 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 20 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 20000
	Send PING to port: 0, time stamp: 20000
time = 20 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 20 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 20.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 20000
time = 20.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 20000
time = 20.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 20000
time = 20.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 20000
time = 20.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 20.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 20.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 20.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 20.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 20000
time = 20.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 20.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 20000
time = 20.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 20.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 20020
time = 20.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 20020
time = 20.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 20020
time = 20.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 20020
time = 20.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 20020
time = 20.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 20020
time = 20.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 20000
time = 20.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 20000
time = 20.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 20.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 20.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 20118
time = 20.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 20118
time = 20.7 Event_Alarm on node 0
time = 20.7 Event_Alarm on node 0
time = 20.7 Event_Alarm on node 2
time = 20.7 Event_Alarm on node 3
time = 21.6 Event_Alarm on node 0
time = 21.6 Event_Alarm on node 0
time = 21.6 Event_Alarm on node 2
time = 21.6 Event_Alarm on node 3
time = 22.5 Event_Alarm on node 0
time = 22.5 Event_Alarm on node 0
time = 22.5 Event_Alarm on node 2
time = 22.5 Event_Alarm on node 3
time = 23.4 Event_Alarm on node 0
time = 23.4 Event_Alarm on node 0
time = 23.4 Event_Alarm on node 2
time = 23.4 Event_Alarm on node 3
time = 24.3 Event_Alarm on node 0
time = 24.3 Event_Alarm on node 0
time = 24.3 Event_Alarm on node 2
time = 24.3 Event_Alarm on node 3
time = 25.2 Event_Alarm on node 0
time = 25.2 Event_Alarm on node 0
time = 25.2 Event_Alarm on node 2
time = 25.2 Event_Alarm on node 3
time = 26.1 Event_Alarm on node 0
time = 26.1 Event_Alarm on node 0
time = 26.1 Event_Alarm on node 2
time = 26.1 Event_Alarm on node 3
time = 27 Event_Alarm on node 0
time = 27 Event_Alarm on node 0
time = 27 Event_Alarm on node 2
time = 27 Event_Alarm on node 3
time = 27.9 Event_Alarm on node 0
time = 27.9 Event_Alarm on node 0
time = 27.9 Event_Alarm on node 2
time = 27.9 Event_Alarm on node 3
time = 28.8 Event_Alarm on node 0
time = 28.8 Event_Alarm on node 0
time = 28.8 Event_Alarm on node 2
time = 28.8 Event_Alarm on node 3
time = 29.7 Event_Alarm on node 0
time = 29.7 Event_Alarm on node 0
time = 29.7 Event_Alarm on node 2
time = 29.7 Event_Alarm on node 3
time = 30 Event_Alarm on node 2
Node 2: protocol update! time: 30000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 30000
  DestID: 4, Cost: 118, NextHop: 2, update: 30000
time = 30 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 30000
	Send PING to port: 0, time stamp: 30000
time = 30 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 30000
	Send PING to port: 0, time stamp: 30000
time = 30 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 30 Event_Alarm on node 0
Node 1: protocol update! time: 30000

  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 30000
  DestID: 3, Cost: 20, NextHop: 1, update: 30000
time = 30 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 30 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 30 Event_Alarm on node 0
Node 4: protocol update! time: 30000

  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
  print DV:
  DestID: 2, Cost: 118, NextHop: 4, update: 30000
  DestID: 3, Cost: 20, NextHop: 4, update: 30000
time = 30 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 30 Event_Xmit_Pkt_On_Link (4,3) packet type is DV
time = 30 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 30 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 30 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 30000
	Send PING to port: 0, time stamp: 30000
time = 30 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 30 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 30 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 30 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 30 Event_Alarm on node 3
Node 3: protocol update! time: 30000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 30000
  DestID: 4, Cost: 20, NextHop: 3, update: 30000
time = 30 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 30 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 30 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 30000
	Send PING to port: 0, time stamp: 30000
time = 30 Event_Xmit_Pkt_On_Link (3,4) packet type is DV
time = 30 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 30 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 30.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 30000
time = 30.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 30000
time = 30.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 30000
time = 30.01 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 4
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 1
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 30000
  DestID: 2, Cost: 138, NextHop: 4, update: 30010
  DestID: 4, Cost: 20, NextHop: 3, update: 30000
time = 30.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 30.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 30.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 30.01 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 30000
  DestID: 3, Cost: 40, NextHop: 1, update: 30010
  DestID: 4, Cost: 118, NextHop: 2, update: 30000
time = 30.01 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 30000
  DestID: 2, Cost: 40, NextHop: 1, update: 30010
  DestID: 4, Cost: 20, NextHop: 3, update: 30000
time = 30.01 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 30.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 30000
time = 30.01 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 1, Port: 1
	Dest: 2, Port: 0
	Dest: 3, Port: 1
  print DV:
  DestID: 1, Cost: 40, NextHop: 3, update: 30010
  DestID: 2, Cost: 118, NextHop: 4, update: 30000
  DestID: 3, Cost: 20, NextHop: 4, update: 30000
time = 30.01 Event_Xmit_Pkt_On_Link (3,4) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (3,4) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 30.01 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (4,3) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 30.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 30000
time = 30.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 30000
time = 30.01 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 30.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 30.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
	Dest: 4, Port: 1
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 30000
  DestID: 3, Cost: 20, NextHop: 1, update: 30000
  DestID: 4, Cost: 40, NextHop: 3, update: 30010
time = 30.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.01 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 30.01 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 30.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 30020
time = 30.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 30020
time = 30.02 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 0
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 30000
  DestID: 3, Cost: 40, NextHop: 1, update: 30020
  DestID: 4, Cost: 60, NextHop: 1, update: 30020
time = 30.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 30020
time = 30.02 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 30.02 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 30.02 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 3
	recvDV: nothing happens.
time = 30.02 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 30.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 30020
time = 30.02 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 30.02 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 1, Port: 1
	Dest: 2, Port: 1
	Dest: 3, Port: 1
  print DV:
  DestID: 1, Cost: 40, NextHop: 3, update: 30020
  DestID: 2, Cost: 60, NextHop: 3, update: 30020
  DestID: 3, Cost: 20, NextHop: 4, update: 30000
time = 30.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 30020
time = 30.02 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 30020
time = 30.02 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
	recvDV: nothing happens.
time = 30.02 Event_Xmit_Pkt_On_Link (4,3) packet type is DV
time = 30.02 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 30.02 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
	recvDV: nothing happens.
time = 30.03 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 30.03 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.059 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 30.059 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 30000
time = 30.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 30.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 30000
time = 30.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 30.069 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 30.069 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.079 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 30.079 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 30.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 30118
time = 30.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 30118
time = 30.6 Event_Alarm on node 0
time = 30.6 Event_Alarm on node 2
time = 30.6 Event_Alarm on node 0
time = 30.6 Event_Alarm on node 3
time = 31.5 Event_Alarm on node 0
time = 31.5 Event_Alarm on node 2
time = 31.5 Event_Alarm on node 0
time = 31.5 Event_Alarm on node 3
time = 32.4 Event_Alarm on node 0
time = 32.4 Event_Alarm on node 2
time = 32.4 Event_Alarm on node 0
time = 32.4 Event_Alarm on node 3
time = 33.3 Event_Alarm on node 0
time = 33.3 Event_Alarm on node 2
time = 33.3 Event_Alarm on node 0
time = 33.3 Event_Alarm on node 3
time = 34.2 Event_Alarm on node 0
time = 34.2 Event_Alarm on node 2
time = 34.2 Event_Alarm on node 0
time = 34.2 Event_Alarm on node 3
time = 35.1 Event_Alarm on node 0
time = 35.1 Event_Alarm on node 2
time = 35.1 Event_Alarm on node 0
time = 35.1 Event_Alarm on node 3
time = 36 Event_Alarm on node 0
time = 36 Event_Alarm on node 2
time = 36 Event_Alarm on node 0
time = 36 Event_Alarm on node 3
time = 36.9 Event_Alarm on node 0
time = 36.9 Event_Alarm on node 2
time = 36.9 Event_Alarm on node 0
time = 36.9 Event_Alarm on node 3
time = 37.8 Event_Alarm on node 0
time = 37.8 Event_Alarm on node 2
time = 37.8 Event_Alarm on node 0
time = 37.8 Event_Alarm on node 3
time = 38.7 Event_Alarm on node 0
time = 38.7 Event_Alarm on node 2
time = 38.7 Event_Alarm on node 0
time = 38.7 Event_Alarm on node 3
time = 39.6 Event_Alarm on node 0
time = 39.6 Event_Alarm on node 2
time = 39.6 Event_Alarm on node 0
time = 39.6 Event_Alarm on node 3
time = 40 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 40000
	Send PING to port: 0, time stamp: 40000
time = 40 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 40000
	Send PING to port: 0, time stamp: 40000
time = 40 Event_Xmit_Data_Pkt source node 2 destination node 4 packet type is DATA
	Packet generated locally, destination: 4.
	Forward the packet through port 0.
time = 40 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 40000
	Send PING to port: 0, time stamp: 40000
time = 40 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 40 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 40000
	Send PING to port: 0, time stamp: 40000
time = 40 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (2,1) packet type is DATA
time = 40 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 40 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 40.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 40000
time = 40.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 40000
time = 40.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 40000
time = 40.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 40000
time = 40.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 40.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 40.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 40.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 40.01 Event_Recv_Pkt_On_Node 1 packet type is DATA
	Forward the packet through port 1.
time = 40.01 Event_Xmit_Pkt_On_Link (1,3) packet type is DATA
time = 40.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 40000
time = 40.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 40.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 40000
time = 40.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 40.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 40020
time = 40.02 Event_Recv_Pkt_On_Node 3 packet type is DATA
	Forward the packet through port 1.
time = 40.02 Event_Xmit_Pkt_On_Link (3,4) packet type is DATA
time = 40.03 Event_Recv_Pkt_On_Node 4 packet type is DATA
	Receive data from 2, No payload in the message.
time = 40.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 40000
time = 40.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 40000
time = 40.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 40.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 40.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 40118
time = 40.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 40118
time = 40.5 Event_Alarm on node 3
time = 40.5 Event_Alarm on node 0
time = 40.5 Event_Alarm on node 0
time = 40.5 Event_Alarm on node 2
time = 41.4 Event_Alarm on node 3
time = 41.4 Event_Alarm on node 0
time = 41.4 Event_Alarm on node 0
time = 41.4 Event_Alarm on node 2
time = 42.3 Event_Alarm on node 3
time = 42.3 Event_Alarm on node 0
time = 42.3 Event_Alarm on node 0
time = 42.3 Event_Alarm on node 2
time = 43.2 Event_Alarm on node 3
time = 43.2 Event_Alarm on node 0
time = 43.2 Event_Alarm on node 0
time = 43.2 Event_Alarm on node 2
time = 44.1 Event_Alarm on node 3
time = 44.1 Event_Alarm on node 0
time = 44.1 Event_Alarm on node 0
time = 44.1 Event_Alarm on node 2
time = 45 Event_Link_Die (3,4)
time = 45 Event_Alarm on node 2
time = 45 Event_Alarm on node 3
time = 45 Event_Alarm on node 0
time = 45 Event_Alarm on node 0
time = 45.9 Event_Alarm on node 2
time = 45.9 Event_Alarm on node 3
time = 45.9 Event_Alarm on node 0
time = 45.9 Event_Alarm on node 0
time = 46.8 Event_Alarm on node 2
time = 46.8 Event_Alarm on node 3
time = 46.8 Event_Alarm on node 0
time = 46.8 Event_Alarm on node 0
time = 47.7 Event_Alarm on node 2
time = 47.7 Event_Alarm on node 3
time = 47.7 Event_Alarm on node 0
time = 47.7 Event_Alarm on node 0
time = 48.6 Event_Alarm on node 2
time = 48.6 Event_Alarm on node 3
time = 48.6 Event_Alarm on node 0
time = 48.6 Event_Alarm on node 0
time = 49.5 Event_Alarm on node 2
time = 49.5 Event_Alarm on node 3
time = 49.5 Event_Alarm on node 0
time = 49.5 Event_Alarm on node 0
time = 50 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 50000
	Send PING to port: 0, time stamp: 50000
time = 50 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 50000
	Send PING to port: 0, time stamp: 50000
time = 50 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 50000
	Send PING to port: 0, time stamp: 50000
time = 50 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 50000
	Send PING to port: 0, time stamp: 50000
time = 50 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 50 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 50 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 50 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
Packet lost
time = 50 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 50 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
Packet lost
time = 50 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 50 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 50.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 50000
time = 50.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 50000
time = 50.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 50000
time = 50.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 50000
time = 50.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 50.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 50.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 50.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 50.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 50020
time = 50.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 50020
time = 50.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 50020
time = 50.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 50020
time = 50.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 50000
time = 50.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 50000
time = 50.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 50.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 50.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 50118
time = 50.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 50118
time = 50.4 Event_Alarm on node 0
time = 50.4 Event_Alarm on node 0
time = 50.4 Event_Alarm on node 2
time = 50.4 Event_Alarm on node 3
time = 51.3 Event_Alarm on node 0
time = 51.3 Event_Alarm on node 0
time = 51.3 Event_Alarm on node 2
time = 51.3 Event_Alarm on node 3
time = 52.2 Event_Alarm on node 0
time = 52.2 Event_Alarm on node 0
time = 52.2 Event_Alarm on node 2
time = 52.2 Event_Alarm on node 3
time = 53.1 Event_Alarm on node 0
time = 53.1 Event_Alarm on node 0
time = 53.1 Event_Alarm on node 2
time = 53.1 Event_Alarm on node 3
time = 54 Event_Alarm on node 0
time = 54 Event_Alarm on node 0
time = 54 Event_Alarm on node 2
time = 54 Event_Alarm on node 3
time = 54.9 Event_Alarm on node 0
time = 54.9 Event_Alarm on node 0
time = 54.9 Event_Alarm on node 2
time = 54.9 Event_Alarm on node 3
time = 55.8 Event_Alarm on node 0
time = 55.8 Event_Alarm on node 0
time = 55.8 Event_Alarm on node 2
time = 55.8 Event_Alarm on node 3
time = 56.7 Event_Alarm on node 0
time = 56.7 Event_Alarm on node 0
time = 56.7 Event_Alarm on node 2
time = 56.7 Event_Alarm on node 3
time = 57.6 Event_Alarm on node 0
time = 57.6 Event_Alarm on node 0
time = 57.6 Event_Alarm on node 2
time = 57.6 Event_Alarm on node 3
time = 58.5 Event_Alarm on node 0
time = 58.5 Event_Alarm on node 0
time = 58.5 Event_Alarm on node 2
time = 58.5 Event_Alarm on node 3
time = 59.4 Event_Alarm on node 0
time = 59.4 Event_Alarm on node 0
time = 59.4 Event_Alarm on node 2
time = 59.4 Event_Alarm on node 3
time = 60 Event_Alarm on node 0
Node 4: protocol update! time: 60000

  Forwarding table: 
	Dest: 2, Port: 0
  print DV:
  DestID: 2, Cost: 118, NextHop: 4, update: 60000
time = 60 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 60000
	Send PING to port: 0, time stamp: 60000
time = 60 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 60000
	Send PING to port: 0, time stamp: 60000
time = 60 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 60000
	Send PING to port: 0, time stamp: 60000
time = 60 Event_Alarm on node 0
Node 1: protocol update! time: 60000

  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
	Dest: 4, Port: 1
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 60000
  DestID: 3, Cost: 20, NextHop: 1, update: 60000
  DestID: 4, Cost: 40, NextHop: 3, update: 30020
time = 60 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 60 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 60 Event_Alarm on node 2
Node 2: protocol update! time: 60000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 0
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 60000
  DestID: 3, Cost: 40, NextHop: 1, update: 30079
  DestID: 4, Cost: 60, NextHop: 1, update: 60000
time = 60 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 60 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 60 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 60 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 60 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 60000
	Send PING to port: 0, time stamp: 60000
time = 60 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 60 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 60 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 60 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
Packet lost
time = 60 Event_Alarm on node 3
Node 3: protocol update! time: 60000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 60000
  DestID: 2, Cost: 40, NextHop: 1, update: 30020
time = 60 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 60 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
Packet lost
time = 60 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 60 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 60.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 60.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 60000
time = 60.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 60000
  DestID: 3, Cost: 20, NextHop: 1, update: 60000
time = 60.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 60000
time = 60.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 60.01 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 60.01 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 60.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 60.01 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 60.01 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 60.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 60000
time = 60.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 60.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 60000
time = 60.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 60.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 60020
time = 60.02 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 60.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 60020
time = 60.02 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 60000
  DestID: 3, Cost: 40, NextHop: 1, update: 60020
  DestID: 4, Cost: 118, NextHop: 2, update: 60020
time = 60.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 60020
time = 60.02 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 60.02 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 60.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 60020
time = 60.03 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
	Dest: 4, Port: 0
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 60000
  DestID: 3, Cost: 20, NextHop: 1, update: 60000
  DestID: 4, Cost: 138, NextHop: 2, update: 60030
time = 60.03 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 60.03 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 60.04 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
	Dest: 4, Port: 0
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 60000
  DestID: 2, Cost: 40, NextHop: 1, update: 60040
  DestID: 4, Cost: 158, NextHop: 1, update: 60040
time = 60.04 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 60.04 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 60.05 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
	recvDV: nothing happens.
time = 60.059 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
	Dest: 3, Port: 0
  print DV:
  DestID: 1, Cost: 138, NextHop: 2, update: 60059
  DestID: 2, Cost: 118, NextHop: 4, update: 60000
  DestID: 3, Cost: 158, NextHop: 2, update: 60059
time = 60.059 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 60.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 60000
time = 60.059 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 60.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 60.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 60000
time = 60.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 60.079 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 60.118 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 60.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 60118
time = 60.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 60118
time = 60.3 Event_Alarm on node 3
time = 60.3 Event_Alarm on node 2
time = 60.3 Event_Alarm on node 0
time = 60.3 Event_Alarm on node 0
time = 61.2 Event_Alarm on node 3
time = 61.2 Event_Alarm on node 2
time = 61.2 Event_Alarm on node 0
time = 61.2 Event_Alarm on node 0
time = 62.1 Event_Alarm on node 3
time = 62.1 Event_Alarm on node 2
time = 62.1 Event_Alarm on node 0
time = 62.1 Event_Alarm on node 0
time = 63 Event_Alarm on node 3
time = 63 Event_Alarm on node 2
time = 63 Event_Alarm on node 0
time = 63 Event_Alarm on node 0
time = 63.9 Event_Alarm on node 3
time = 63.9 Event_Alarm on node 2
time = 63.9 Event_Alarm on node 0
time = 63.9 Event_Alarm on node 0
time = 64.8 Event_Alarm on node 3
time = 64.8 Event_Alarm on node 2
time = 64.8 Event_Alarm on node 0
time = 64.8 Event_Alarm on node 0
time = 65.7 Event_Alarm on node 3
time = 65.7 Event_Alarm on node 2
time = 65.7 Event_Alarm on node 0
time = 65.7 Event_Alarm on node 0
time = 66.6 Event_Alarm on node 3
time = 66.6 Event_Alarm on node 2
time = 66.6 Event_Alarm on node 0
time = 66.6 Event_Alarm on node 0
time = 67.5 Event_Alarm on node 3
time = 67.5 Event_Alarm on node 2
time = 67.5 Event_Alarm on node 0
time = 67.5 Event_Alarm on node 0
time = 68.4 Event_Alarm on node 3
time = 68.4 Event_Alarm on node 2
time = 68.4 Event_Alarm on node 0
time = 68.4 Event_Alarm on node 0
time = 69.3 Event_Alarm on node 3
time = 69.3 Event_Alarm on node 2
time = 69.3 Event_Alarm on node 0
time = 69.3 Event_Alarm on node 0
time = 70 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 70000
	Send PING to port: 0, time stamp: 70000
time = 70 Event_Xmit_Data_Pkt source node 2 destination node 4 packet type is DATA
	Packet generated locally, destination: 4.
	Forward the packet through port 1.
time = 70 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 70000
	Send PING to port: 0, time stamp: 70000
time = 70 Event_Xmit_Pkt_On_Link (2,4) packet type is DATA
time = 70 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 70000
	Send PING to port: 0, time stamp: 70000
time = 70 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 70 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
Packet lost
time = 70 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 70 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 70000
	Send PING to port: 0, time stamp: 70000
time = 70 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 70 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 70 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 70 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
Packet lost
time = 70 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 70.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 70000
time = 70.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 70000
time = 70.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 70000
time = 70.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 70000
time = 70.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 70.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 70.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 70.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 70.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 70020
time = 70.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 70020
time = 70.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 70020
time = 70.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 70020
time = 70.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 70000
time = 70.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 70000
time = 70.059 Event_Recv_Pkt_On_Node 4 packet type is DATA
	Receive data from 2, No payload in the message.
time = 70.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 70.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 70.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 70118
time = 70.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 70118
time = 70.2 Event_Alarm on node 0
time = 70.2 Event_Alarm on node 0
time = 70.2 Event_Alarm on node 2
time = 70.2 Event_Alarm on node 3
time = 71 Event_Xmit_Data_Pkt source node 4 destination node 2 packet type is DATA
	Packet generated locally, destination: 2.
	Forward the packet through port 0.
time = 71 Event_Xmit_Pkt_On_Link (4,2) packet type is DATA
time = 71.059 Event_Recv_Pkt_On_Node 2 packet type is DATA
	Receive data from 4, No payload in the message.
time = 71.1 Event_Alarm on node 0
time = 71.1 Event_Alarm on node 0
time = 71.1 Event_Alarm on node 3
time = 71.1 Event_Alarm on node 2
time = 72 Event_Alarm on node 0
time = 72 Event_Alarm on node 0
time = 72 Event_Alarm on node 2
time = 72 Event_Alarm on node 3
time = 72.9 Event_Alarm on node 0
time = 72.9 Event_Alarm on node 0
time = 72.9 Event_Alarm on node 3
time = 72.9 Event_Alarm on node 2
time = 73.8 Event_Alarm on node 0
time = 73.8 Event_Alarm on node 0
time = 73.8 Event_Alarm on node 2
time = 73.8 Event_Alarm on node 3
time = 74.7 Event_Alarm on node 0
time = 74.7 Event_Alarm on node 0
time = 74.7 Event_Alarm on node 3
time = 74.7 Event_Alarm on node 2
time = 75.6 Event_Alarm on node 0
time = 75.6 Event_Alarm on node 0
time = 75.6 Event_Alarm on node 2
time = 75.6 Event_Alarm on node 3
time = 76.5 Event_Alarm on node 0
time = 76.5 Event_Alarm on node 0
time = 76.5 Event_Alarm on node 3
time = 76.5 Event_Alarm on node 2
time = 77.4 Event_Alarm on node 0
time = 77.4 Event_Alarm on node 0
time = 77.4 Event_Alarm on node 2
time = 77.4 Event_Alarm on node 3
time = 78.3 Event_Alarm on node 0
time = 78.3 Event_Alarm on node 0
time = 78.3 Event_Alarm on node 3
time = 78.3 Event_Alarm on node 2
time = 79.2 Event_Alarm on node 0
time = 79.2 Event_Alarm on node 0
time = 79.2 Event_Alarm on node 2
time = 79.2 Event_Alarm on node 3
time = 80 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 80000
	Send PING to port: 0, time stamp: 80000
time = 80 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 80 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 80000
	Send PING to port: 0, time stamp: 80000
time = 80 Event_Link_Come_Up (3,4)
time = 80 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 80000
	Send PING to port: 0, time stamp: 80000
time = 80 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 80000
	Send PING to port: 0, time stamp: 80000
time = 80 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 80 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 80.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 80000
time = 80.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 80000
time = 80.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 80000
time = 80.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 80000
time = 80.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 80.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 80.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 80.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 80.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 80000
time = 80.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 80000
time = 80.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 80.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 80.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 80020
time = 80.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 80020
time = 80.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 80020
time = 80.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 80020
time = 80.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 80020
time = 80.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 80020
time = 80.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 80000
time = 80.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 80000
time = 80.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 80.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 80.1 Event_Alarm on node 0
time = 80.1 Event_Alarm on node 3
time = 80.1 Event_Alarm on node 0
time = 80.1 Event_Alarm on node 2
time = 80.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 80118
time = 80.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 80118
time = 81 Event_Alarm on node 0
time = 81 Event_Alarm on node 3
time = 81 Event_Alarm on node 0
time = 81 Event_Alarm on node 2
time = 81.9 Event_Alarm on node 0
time = 81.9 Event_Alarm on node 3
time = 81.9 Event_Alarm on node 2
time = 81.9 Event_Alarm on node 0
time = 82.8 Event_Alarm on node 0
time = 82.8 Event_Alarm on node 3
time = 82.8 Event_Alarm on node 0
time = 82.8 Event_Alarm on node 2
time = 83.7 Event_Alarm on node 0
time = 83.7 Event_Alarm on node 3
time = 83.7 Event_Alarm on node 2
time = 83.7 Event_Alarm on node 0
time = 84.6 Event_Alarm on node 0
time = 84.6 Event_Alarm on node 3
time = 84.6 Event_Alarm on node 0
time = 84.6 Event_Alarm on node 2
time = 85.5 Event_Alarm on node 0
time = 85.5 Event_Alarm on node 3
time = 85.5 Event_Alarm on node 2
time = 85.5 Event_Alarm on node 0
time = 86.4 Event_Alarm on node 0
time = 86.4 Event_Alarm on node 3
time = 86.4 Event_Alarm on node 0
time = 86.4 Event_Alarm on node 2
time = 87.3 Event_Alarm on node 0
time = 87.3 Event_Alarm on node 3
time = 87.3 Event_Alarm on node 2
time = 87.3 Event_Alarm on node 0
time = 88.2 Event_Alarm on node 0
time = 88.2 Event_Alarm on node 3
time = 88.2 Event_Alarm on node 0
time = 88.2 Event_Alarm on node 2
time = 89.1 Event_Alarm on node 0
time = 89.1 Event_Alarm on node 3
time = 89.1 Event_Alarm on node 2
time = 89.1 Event_Alarm on node 0
time = 90 Event_Alarm on node 0
time = 90 Event_Alarm on node 3
time = 90 Event_Alarm on node 0
time = 90 Event_Alarm on node 0
Node 1: protocol update! time: 90000

  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
	Dest: 4, Port: 0
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 90000
  DestID: 3, Cost: 20, NextHop: 1, update: 90000
  DestID: 4, Cost: 138, NextHop: 2, update: 60030
time = 90 Event_Alarm on node 0
Node 4: protocol update! time: 90000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
	Dest: 3, Port: 1
  print DV:
  DestID: 1, Cost: 138, NextHop: 2, update: 60079
  DestID: 2, Cost: 118, NextHop: 4, update: 90000
  DestID: 3, Cost: 20, NextHop: 4, update: 90000
time = 90 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 90 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 90 Event_Alarm on node 2
Node 2: protocol update! time: 90000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 90000
  DestID: 3, Cost: 40, NextHop: 1, update: 60040
  DestID: 4, Cost: 118, NextHop: 2, update: 90000
time = 90 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 90000
	Send PING to port: 0, time stamp: 90000
time = 90 Event_Alarm on node 3
Node 3: protocol update! time: 90000

  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 2, Port: 0
	Dest: 4, Port: 1
  print DV:
  DestID: 1, Cost: 20, NextHop: 3, update: 90000
  DestID: 2, Cost: 40, NextHop: 1, update: 60040
  DestID: 4, Cost: 20, NextHop: 3, update: 90000
time = 90 Event_Alarm on node 2
time = 90 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (3,1) packet type is DV
time = 90 Event_Xmit_Pkt_On_Link (3,4) packet type is DV
time = 90 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 90 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 90000
	Send PING to port: 0, time stamp: 90000
time = 90 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 90 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 90000
	Send PING to port: 0, time stamp: 90000
time = 90 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 90 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 90 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 90000
	Send PING to port: 0, time stamp: 90000
time = 90 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 90 Event_Xmit_Pkt_On_Link (4,3) packet type is DV
time = 90 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 90.01 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 90.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 90000
time = 90.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 90000
time = 90.01 Event_Recv_Pkt_On_Node 1 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 90000
time = 90.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 90.01 Event_Xmit_Pkt_On_Link (4,3) packet type is PONG
time = 90.01 Event_Xmit_Pkt_On_Link (1,3) packet type is PONG
time = 90.01 Event_Xmit_Pkt_On_Link (1,2) packet type is PONG
time = 90.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 90000
time = 90.01 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 90.01 Event_Xmit_Pkt_On_Link (3,4) packet type is PONG
time = 90.01 Event_Recv_Pkt_On_Node 3 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 90000
time = 90.01 Event_Xmit_Pkt_On_Link (3,1) packet type is PONG
time = 90.01 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 2, Port: 0
	Dest: 3, Port: 1
	Dest: 4, Port: 1
  print DV:
  DestID: 2, Cost: 20, NextHop: 1, update: 90000
  DestID: 3, Cost: 20, NextHop: 1, update: 90000
  DestID: 4, Cost: 40, NextHop: 3, update: 90010
time = 90.01 Event_Xmit_Pkt_On_Link (1,2) packet type is DV
time = 90.01 Event_Xmit_Pkt_On_Link (1,3) packet type is DV
time = 90.01 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 90.01 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 3
  Forwarding table: 
	Dest: 1, Port: 1
	Dest: 2, Port: 1
	Dest: 3, Port: 1
  print DV:
  DestID: 1, Cost: 40, NextHop: 3, update: 90010
  DestID: 2, Cost: 60, NextHop: 3, update: 90010
  DestID: 3, Cost: 20, NextHop: 4, update: 90000
time = 90.01 Event_Xmit_Pkt_On_Link (4,2) packet type is DV
time = 90.01 Event_Xmit_Pkt_On_Link (4,3) packet type is DV
time = 90.01 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 0, source: 1, time stamp: 90000
time = 90.01 Event_Xmit_Pkt_On_Link (2,1) packet type is PONG
time = 90.02 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 1
  Forwarding table: 
	Dest: 1, Port: 0
	Dest: 3, Port: 0
	Dest: 4, Port: 0
  print DV:
  DestID: 1, Cost: 20, NextHop: 2, update: 90000
  DestID: 3, Cost: 40, NextHop: 1, update: 90020
  DestID: 4, Cost: 60, NextHop: 1, update: 90020
time = 90.02 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 1
	recvDV: nothing happens.
time = 90.02 Event_Recv_Pkt_On_Node 3 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 90.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 20, time: 90020
time = 90.02 Event_Xmit_Pkt_On_Link (2,1) packet type is DV
time = 90.02 Event_Xmit_Pkt_On_Link (2,4) packet type is DV
time = 90.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 20, time: 90020
time = 90.02 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 90020
time = 90.02 Event_Recv_Pkt_On_Node 3 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 90020
time = 90.02 Event_Recv_Pkt_On_Node 1 packet type is PONG
	Receive PONG: from port 1, source: 3, duration: 20, time: 90020
time = 90.02 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 0, source: 1, duration: 20, time: 90020
time = 90.03 Event_Recv_Pkt_On_Node 1 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 90.059 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 90.059 Event_Recv_Pkt_On_Node 2 packet type is PING
	Receive PING: from port 1, source: 4, time stamp: 90000
time = 90.059 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 90.059 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 0, source: 2, time stamp: 90000
time = 90.059 Event_Xmit_Pkt_On_Link (2,4) packet type is PONG
time = 90.059 Event_Xmit_Pkt_On_Link (4,2) packet type is PONG
time = 90.069 Event_Recv_Pkt_On_Node 2 packet type is DV
	receive from 4
	recvDV: nothing happens.
time = 90.079 Event_Recv_Pkt_On_Node 4 packet type is DV
	receive from 2
	recvDV: nothing happens.
time = 90.118 Event_Recv_Pkt_On_Node 4 packet type is PONG
	Receive PONG: from port 0, source: 2, duration: 118, time: 90118
time = 90.118 Event_Recv_Pkt_On_Node 2 packet type is PONG
	Receive PONG: from port 1, source: 4, duration: 118, time: 90118
time = 90.9 Event_Alarm on node 2
time = 90.9 Event_Alarm on node 0
time = 90.9 Event_Alarm on node 3
time = 90.9 Event_Alarm on node 0
time = 91.8 Event_Alarm on node 2
time = 91.8 Event_Alarm on node 0
time = 91.8 Event_Alarm on node 0
time = 91.8 Event_Alarm on node 3
time = 92.7 Event_Alarm on node 2
time = 92.7 Event_Alarm on node 0
time = 92.7 Event_Alarm on node 3
time = 92.7 Event_Alarm on node 0
time = 93.6 Event_Alarm on node 2
time = 93.6 Event_Alarm on node 0
time = 93.6 Event_Alarm on node 0
time = 93.6 Event_Alarm on node 3
time = 94.5 Event_Alarm on node 2
time = 94.5 Event_Alarm on node 0
time = 94.5 Event_Alarm on node 3
time = 94.5 Event_Alarm on node 0
time = 95 Event_Xmit_Data_Pkt source node 2 destination node 4 packet type is DATA
	Packet generated locally, destination: 4.
	Forward the packet through port 0.
time = 95 Event_Xmit_Pkt_On_Link (2,1) packet type is DATA
time = 95.01 Event_Recv_Pkt_On_Node 1 packet type is DATA
	Forward the packet through port 1.
time = 95.01 Event_Xmit_Pkt_On_Link (1,3) packet type is DATA
time = 95.02 Event_Recv_Pkt_On_Node 3 packet type is DATA
	Forward the packet through port 1.
time = 95.02 Event_Xmit_Pkt_On_Link (3,4) packet type is DATA
time = 95.03 Event_Recv_Pkt_On_Node 4 packet type is DATA
	Receive data from 2, No payload in the message.
time = 95.4 Event_Alarm on node 2
time = 95.4 Event_Alarm on node 0
time = 95.4 Event_Alarm on node 3
time = 95.4 Event_Alarm on node 0
time = 96.3 Event_Alarm on node 2
time = 96.3 Event_Alarm on node 0
time = 96.3 Event_Alarm on node 0
time = 96.3 Event_Alarm on node 3
time = 97.2 Event_Alarm on node 2
time = 97.2 Event_Alarm on node 0
time = 97.2 Event_Alarm on node 3
time = 97.2 Event_Alarm on node 0
time = 98.1 Event_Alarm on node 2
time = 98.1 Event_Alarm on node 0
time = 98.1 Event_Alarm on node 0
time = 98.1 Event_Alarm on node 3
time = 99 Event_Alarm on node 2
time = 99 Event_Alarm on node 0
time = 99 Event_Alarm on node 3
time = 99 Event_Alarm on node 0
time = 99.9 Event_Alarm on node 2
time = 99.9 Event_Alarm on node 0
time = 99.9 Event_Alarm on node 0
time = 99.9 Event_Alarm on node 3
time = 100 Event_Alarm on node 3
  Node 3: pingpong message!
	Send PING to port: 1, time stamp: 100000
	Send PING to port: 0, time stamp: 100000
time = 100 Event_Xmit_Pkt_On_Link (3,4) packet type is PING
time = 100 Event_Xmit_Pkt_On_Link (3,1) packet type is PING
time = 100 Event_Alarm on node 2
  Node 2: pingpong message!
	Send PING to port: 1, time stamp: 100000
	Send PING to port: 0, time stamp: 100000
time = 100 Event_Xmit_Pkt_On_Link (2,4) packet type is PING
time = 100 Event_Alarm on node 0
  Node 4: pingpong message!
	Send PING to port: 1, time stamp: 100000
	Send PING to port: 0, time stamp: 100000
time = 100 Event_Alarm on node 0
  Node 1: pingpong message!
	Send PING to port: 1, time stamp: 100000
	Send PING to port: 0, time stamp: 100000
time = 100 Event_Xmit_Pkt_On_Link (2,1) packet type is PING
time = 100 Event_Xmit_Pkt_On_Link (1,2) packet type is PING
time = 100 Event_Xmit_Pkt_On_Link (4,2) packet type is PING
time = 100 Event_Xmit_Pkt_On_Link (1,3) packet type is PING
time = 100 Event_Xmit_Pkt_On_Link (4,3) packet type is PING
time = 100.01 Event_Recv_Pkt_On_Node 4 packet type is PING
	Receive PING: from port 1, source: 3, time stamp: 100000
Simulator has ended.
