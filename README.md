OscMessageParser
================

Simple C++ implementation of OSC message parsing functionality.

Algorithm
|           |s0:idle    |s1:addr    |s2:tag     |s3:param   |s4:stored  |
|adr-rcv    |s1         |s1         |x          |x          |x          |
|adr-don    |x          |s2         |x          |x          |x          |
|adr-err    |x          |s0         |x          |x          |x          |
|tag-rcv    |x          |x          |s2         |x          |x          |
|tag-prm    |x          |x          |s3         |x          |x          |
|tag-non    |x          |x          |s4         |x          |x          |
|tag-err    |x          |x          |s0         |x          |x          |
|prm-rcv    |x          |x          |x          |s3         |x          |
|prm-don    |x          |x          |x          |s4         |x          |
|prm-err    |x          |x          |x          |s0         |x          |

addr
|           |s0:idle    |s1:nonslash|s2:str     |s3:padding |s4:done    |s5:err |
|/          |s1         |s5         |s1         |s5         |s1         |s1     |
|ascii      |s5         |s2         |s2         |s5         |s5         |-      |
|\0         |-          |s5         |s3         |-          |-          |-      |
|\0/4       |-          |s5         |s4         |s4         |-          |-      |
|read       |s0         |s0         |s0         |s0         |s0         |s0     |
|flush      |s0         |s0         |s0         |s0         |s0         |s0     |

tag
|           |s0:idle    |s1:tag     |s2:padding |s3:done    |:err   |
|,          |s1         |err        |err        |s1         |s1     |
|i/f/s/b    |err        |-          |err        |err        |-      |
|\0         |-          |s2         |-          |-          |-      |
|\0/4       |-          |s3         |s3         |-          |-      |
|ascii      |err        |err        |err        |err        |-      |
|read       |s0         |s0         |s0         |s0         |s0     |
|flush      |s0         |s0         |s0         |s0         |s0     |

param
|           |s0:idle    |s1:parsing |s2:don |
|idle       |s1         |s1         |-      |
|inprocess  |x          |s1         |x      |
|done       |s2         |s2         |x      |


refs
http://opensoundcontrol.org/spec-1_0-examples#OSCaddress
