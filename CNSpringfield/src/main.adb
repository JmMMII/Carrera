--Autores--
--Andrea Rodriguez Lozano
--Jiaming He

with Text_IO;
use Text_IO;

with Central;
use Central;
with Ada.Real_Time;
use Ada.Real_Time;
with Ada.Numerics.Discrete_Random;
procedure Main is

   type Reactores is array (1..3) of aliased Reactor;

   subtype aleatorioReactor is Integer range 1..3;
   package Aleatorio is new Ada.Numerics.Discrete_Random(aleatorioReactor);
   seed : Aleatorio.Generator;

   task type IncrementarAleatorio (rc: access Reactores);
   task body IncrementarAleatorio is
      temp: Integer;
      hora: Time;
      intervalo: Time_Span:=Seconds(10);
   begin
      loop
         hora:=Clock + intervalo;
         Aleatorio.reset(seed);
         temp:=Aleatorio.Random(seed);
         Put_Line("Incrementando "&temp'Image);
         rc(temp).incrementar;
         delay until hora;
      end loop;
   end IncrementarAleatorio;

   task type Coordinadora (numero:Integer) is
      entry avisar;
   end Coordinadora;

   task body Coordinadora is
   begin
      loop
      select
         accept avisar do
            begin
                  --Put_Line("Sensor "&numero'Image&" online.");
                  null;
            end;
         end avisar;
      or
         delay 3.0;
            Put_Line("Sensor "&numero'Image&" offline");
         end select;
      end loop;
   end Coordinadora;



   task type Sensor (rc: access Reactor; numero: Integer) is
      end Sensor;
   task body Sensor is
      hora:Time;
      intervalo:Time_Span:=Seconds(2);
      temperatura: Integer;
      cerrado:Boolean:=True;
      coord:Coordinadora(numero);
   begin
      loop
         hora:=Clock + intervalo;
         rc.leer(temperatura);
         coord.avisar;
         Put_Line("Reactor "&numero'Image&" Temperatura: "&temperatura'Image);
         if temperatura > 1750 then
            Put_Line("¡¡Reactor "&numero'image&" :temperatura superior a 1750C!!");

            if cerrado then
                  cerrado:=False;
               Put_Line("Abriendo compuerta "&numero'image);
            end if;

            rc.abrir;

         else
            if temperatura >=1500 then

               if cerrado then
                  cerrado:=False;
                  Put_Line("Abriendo compuerta "&numero'image);
               end if;

               rc.abrir;

            else
               if not cerrado then
                  cerrado:=True;
                  Put_Line("Cerrando compuerta "&numero'image);
               end if;

               rc.cerrar;

            end if;
         end if;

         delay until hora;
      end loop;
   end Sensor;

   procedure inicio is
      rc: aliased Reactores;
      a: IncrementarAleatorio(rc'Access);
      b: Sensor(rc(1)'Access,1);
      c: Sensor(rc(2)'access,2);
      d: Sensor(rc(3)'access,3);
   begin
      null;
   end inicio;

begin
   inicio;
end Main;
