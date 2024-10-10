case BAROMETRE :	   {	double var1, var2;
							double Tfine, Pfine;

					        var1 = (((double) tp_data.temp)/16384.0 - T1/1024.0) * T2;
					        var2 = ((((double) tp_data.temp)/131072.0 - T1/8192.0) * (((double) tp_data.temp)/131072.0 - T1/8192.0)) * T3;
					        Tfine = (var1 + var2);
					        Data.Data[0] = ((var1 + var2) / 5120.0);
	
					        var1 = (Tfine/2.0) - 64000.0;
					        var2 = var1 * var1 * P6/32768.0;
					        var2 = var2 + var1 * P5*2.0;
					        var2 = (var2/4.0) + (P4*65536.0);
					        var1 = ((P3 * var1 * var1)/524288.0 + P2*var1)/524288.0;
					        var1 = (1.0 + var1/32768.0)*P1;
					        Pfine = (1048576.0 - (double) tp_data.data[0]);
					        if (var1 < 0 || var1 > 0)
					        {
					        	Pfine = ((Pfine - (var2/4096.0))*(6250.0/var1));
					            var1 = (P9*Pfine*Pfine)/2147483648.0;
					            var2 = (Pfine* P8)/32768.0;
					            Data.Data[1] = (Pfine + (var1 + var2 + P7)/16.0);
					        }
					        else
					        {
					        	Data.Data[1] = 0;
					        }
					   }
					   break;

