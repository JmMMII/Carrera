with Ada.Real_Time;
with Ada.Real_Time.Timing_Events;

package Central is
   jitterControl: Ada.Real_Time.Timing_Events.Timing_Event;
   protected type Reactor is
      
      procedure incrementar;
      procedure leer(valor: out Integer);
      procedure reducir (event: in out Ada.Real_Time.Timing_Events.Timing_Event);
      procedure abrir;
      procedure cerrar;
      
   private
      temp:Integer:=1450;
      hora: Ada.Real_Time.Time;
   end Reactor;

end Central;
