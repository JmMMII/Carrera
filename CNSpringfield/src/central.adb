with Text_IO;
use Text_IO;

with Ada.Real_Time;
with Ada.Real_Time.Timing_Events;
use Ada.Real_Time;

package body Central is

   protected body Reactor is
      
      procedure incrementar is
      begin
         temp := temp + 150;
      end incrementar;
        
      procedure leer(valor: out integer) is
         intervalo: Time_Span:=Milliseconds(100);
      begin
         hora:= Clock + intervalo;
         valor:=temp;
         delay until hora;
      end leer;
      
      procedure reducir (event: in out Ada.Real_Time.Timing_Events.Timing_Event) is
         intervalo:Time_Span:=Seconds(1);
      begin
         temp := temp - 50;
         Put_Line("Temperatura: "&temp'Image);
         hora:=Clock + intervalo;
         Ada.Real_Time.Timing_Events.Set_Handler(jitterControl, hora, reducir'Access);
      end reducir;
      
      procedure abrir is
         intervalo:Time_Span:=Seconds(1);
      begin
         hora:=Clock + intervalo;
         Ada.Real_Time.Timing_Events.Set_Handler(jitterControl,hora,reducir'Access);
      end abrir;
      
      procedure cerrar is
      begin
         hora:=Clock;
         Ada.Real_Time.Timing_Events.Set_Handler(jitterControl,hora,null);
      end cerrar;
      
   end Reactor;
   
end Central;
