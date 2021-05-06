  #define TMCRhino_GCONF        0x00
  #define TMCRhino_GSTAT        0x01
  #define TMCRhino_IFCNT        0x02
  #define TMCRhino_SLAVECONF    0x03
  #define TMCRhino_INP_OUT      0x04
  #define TMCRhino_X_COMPARE    0x05
  #define TMCRhino_IHOLD_IRUN   0x10
  #define TMCRhino_TZEROWAIT    0x11
  #define TMCRhino_TSTEP      0x12
  #define TMCRhino_TPWMTHRS     0x13
  #define TMCRhino_TCOOLTHRS    0x14
  #define TMCRhino_THIGH        0x15

  #define TMCRhino_RAMPMODE     0x20
  #define TMCRhino_XACTUAL      0x21
  #define TMCRhino_VACTUAL      0x22
  #define TMCRhino_VSTART       0x23
  #define TMCRhino_A1           0x24
  #define TMCRhino_V1           0x25
  #define TMCRhino_AMAX         0x26
  #define TMCRhino_VMAX         0x27
  #define TMCRhino_DMAX         0x28
  #define TMCRhino_D1           0x2A
  #define TMCRhino_VSTOP        0x2B
  #define TMCRhino_TZEROCROSS   0x2C
  #define TMCRhino_XTARGET      0x2D


  #define TMCRhino_VDCMIN       0x33
  #define TMCRhino_SWMODE       0x34
  #define TMCRhino_RAMPSTAT     0x35
  #define TMCRhino_XLATCH       0x36
  #define TMCRhino_ENCMODE      0x38
  #define TMCRhino_XENC         0x39
  #define TMCRhino_ENC_CONST    0x3A
  #define TMCRhino_ENC_STATUS   0x3B
  #define TMCRhino_ENC_LATCH    0x3C

  #define TMCRhino_MSLUT0       0x60
  #define TMCRhino_MSLUT1       0x61
  #define TMCRhino_MSLUT2       0x62
  #define TMCRhino_MSLUT3       0x63
  #define TMCRhino_MSLUT4       0x64
  #define TMCRhino_MSLUT5       0x65
  #define TMCRhino_MSLUT6       0x66
  #define TMCRhino_MSLUT7       0x67
  #define TMCRhino_MSLUTSEL     0x68
  #define TMCRhino_MSLUTSTART   0x69
  #define TMCRhino_MSCNT        0x6A
  #define TMCRhino_MSCURACT     0x6B
  #define TMCRhino_CHOPCONF     0x6C
  #define TMCRhino_COOLCONF     0x6D
  #define TMCRhino_DCCTRL       0x6E
  #define TMCRhino_DRVSTATUS    0x6F
  #define TMCRhino_PWMCONF      0x70
  #define TMCRhino_PWMSTATUS    0x71
  #define TMCRhino_EN_CTRL    0x72
  #define TMCRhino_LOST_STEPS   0x73

  //Rampenmodi (Register TMCRhino_RAMPMODE)
  #define TMCRhino_MODE_POSITION   0
  #define TMCRhino_MODE_VELPOS     1
  #define TMCRhino_MODE_VELNEG     2
  #define TMCRhino_MODE_HOLD       3

  //Endschaltermodusbits (Register TMCRhino_SWMODE)
  #define TMCRhino_SW_STOPL_ENABLE   0x0001
  #define TMCRhino_SW_STOPR_ENABLE   0x0002
  #define TMCRhino_SW STOPL_POLARITY 0x0004
  #define TMCRhino_SW_STOPR_POLARITY 0x0008
  #define TMCRhino_SW_SWAP_LR        0x0010
  #define TMCRhino_SW_LATCH_L_ACT    0x0020
  #define TMCRhino_SW_LATCH_L_INACT  0x0040
  #define TMCRhino_SW_LATCH_R_ACT    0x0080
  #define TMCRhino_SW_LATCH_R_INACT  0x0100
  #define TMCRhino_SW_LATCH_ENC      0x0200
  #define TMCRhino_SW_SG_STOP        0x0400
  #define TMCRhino_SW_SOFTSTOP       0x0800


  //Statusbitss (Register TMCRhino_RAMPSTAT)
  #define TMCRhino_RS_STOPL          0x0001
  #define TMCRhino_RS_STOPR          0x0002
  #define TMCRhino_RS_LATCHL         0x0004
  #define TMCRhino_RS_LATCHR         0x0008
  #define TMCRhino_RS_EV_STOPL       0x0010
  #define TMCRhino_RS_EV_STOPR       0x0020
  #define TMCRhino_RS_EV_STOP_SG     0x0040
  #define TMCRhino_RS_EV_POSREACHED  0x0080
  #define TMCRhino_RS_VELREACHED     0x0100
  #define TMCRhino_RS_POSREACHED     0x0200
  #define TMCRhino_RS_VZERO          0x0400
  #define TMCRhino_RS_ZEROWAIT       0x0800
  #define TMCRhino_RS_SECONDMOVE     0x1000
  #define TMCRhino_RS_SG             0x2000
