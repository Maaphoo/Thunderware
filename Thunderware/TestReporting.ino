





//void reportSettings(){
//  Serial.print("Auger Speed: ");
//  Serial.println(augerRPM);
//  
//  Serial.print("Outfeed Speed: ");
//  Serial.println(outfeedRPM);
//  
//  Serial.print("Temp Set Point: ");
//  Serial.println(*tempSetPoint);
//  
//  Serial.println("");
//}

void reportCurrentMeasurementTitles(){
  
  Serial.println("Time(s), Dia(mm), Barrel Temp(C), BarrelDutyCycle(%), Nozzle Temp(c), NozzleDutyCycle(%), augerRPM, outfeedRPM, spoolRPM, steps, FeedRate");
 
}

void reportCurrentMeasurements(){
  
  //Serial.println("Barrel_Temp Nozzle_Temp Duty_Cycle Diameter");
   Serial.print((now-startExtrudingTime)/1000);
   
//   Serial.print(", ");
//   Serial.print(mmExtruded/(25.4*12));//feet bc that's what my tape measure is.
       
   Serial.print(", ");
   Serial.print(medianDia,3);
   
   Serial.print(", ");
   Serial.print(barrelTemp,2);

   Serial.print(", ");
   Serial.print(barrelDutyCycle);
        
   Serial.print(", ");
   Serial.print(nozzleTemp,2);
   
   Serial.print(", ");
   Serial.print(nozzleDutyCycle);
   
   Serial.print(", ");
   Serial.print(augerRPM);
   
   Serial.print(", ");
   Serial.print(outfeedRPM);
   
   Serial.print(", ");
   Serial.print(spoolRPM);

   
   Serial.print(", ");
   Serial.print(getFeedRate());   
   
   Serial.print(", ");
   Serial.print(getFeederState()); 
   
   Serial.println(); 
}

//void reportArray(){
//   if (k<172){//build array
//    *(array+k) = now/1000;
//    k++;
//    *(array+k) = mmExtruded/(25.4*12.0);
//    k++;
//    *(array+k) = medianDia;
//    k++;
//    *(array+k) = barrelTemp;
//    k++;
//    *(array+k) = nozzleTemp;
//    k++;
//    *(array+k) = dutyCycle;
//    k++;
//    *(array+k) = aStepInterval;
//    k++;
//    *(array+k) = oStepInterval;
//    k++;
//    *(array+k) = sStepInterval;
//    k++;
//    }else{
//    i = 0;
//    while (i<180){   
//     Serial.print(*(array+i));
//     i++;
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;     
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;     
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;    
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;    
//     Serial.print(", ");
//     Serial.print(*(array+i));
//     i++;    
//     Serial.println();
//  }   
//    k=0;//reset counter
//    //capture this second's data
//    *(array+k) = now/1000;
//    k++;
//    *(array+k) = mmExtruded/25.4*12.0;
//    k++;
//    *(array+k) = medianDia;
//    k++;
//    *(array+k) = barrelTemp;
//    k++;
//    *(array+k) = nozzleTemp;
//    k++;
//    *(array+k) = dutyCycle;
//    k++;
//    *(array+k) = aStepInterval;
//    k++;
//    *(array+k) = oStepInterval;
//    k++;
//    *(array+k) = sStepInterval;
//    k++;
//  }
// }
// 
//void reportDiameter(){
//   Serial.println(caliperReading);
// }
// 
//void reportSPS(){
//  Serial.print("AugerSPS: ");
//  Serial.print(augerSPS);
//  Serial.print("  outfeedSPS: ");
//  Serial.print(outfeedSPS);  
//  Serial.print("  spoolSPS: ");
//  Serial.println(spoolSPS);
//}
//
//void reportDiaVTime(){
//  Serial.print(now/1000); 
//  Serial.print(", "); 
//  Serial.print(caliperReading, 3);
//  Serial.print(", "); 
//  Serial.print(barrelTemp); 
//  Serial.print(", "); 
//  Serial.println(nozzleTemp); 
//}
//
//void reportCaliper(){
//     Serial.print(now/1000);
//   Serial.print(", ");
//   Serial.print(caliperReading,3);
//   Serial.print(", ");
//   Serial.print(medianDia,3);
//      Serial.print(" Readings: ");
//
//   for (int i=0;i<7;i++){
//        Serial.print("  ");
//   Serial.print(*(diaMeasurements+i),3);
//   }
//
//   Serial.println(); 
//
//}
//

