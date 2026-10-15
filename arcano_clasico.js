function arcano_clasico () {


  var H1=0; var H2=0; var H4=0; var H8=0;
  var M1=0; var M2=0; var M4=0; var M8=0;

 
 let f =new Date();
 var hora=f.getHours();
 var min=f.getMinutes();

  var cuarthora= Math.floor(hora/15);
  var hcto= Math.floor(hora-cuarthora*15);

  var cuartminuto= Math.floor(min/15);
   var mcto= Math.floor(min-cuartminuto*15);


if (min != min_a) {

  console.log("entro")
 
   //hora

  if (cuarthora == 1){H1=2}else{H1=0}

      if (hcto == 1 || hcto==3 || hcto ==5 || hcto == 7 ||hcto == 9 || hcto ==11|| hcto==13) 	{H1++;}

     if (hcto == 2 || hcto==3 || hcto ==6 || hcto == 7 ||hcto == 10 || hcto ==11|| hcto==14)	{H2++;}

  if (hcto == 4 || hcto==5 || hcto ==6 || hcto == 7 ||hcto == 12 || hcto ==13|| hcto==14)	{H4++;}

  if (hcto > 7)	{H8++;}

  
  ///minutos

  switch(cuartminuto){ 

          case 1:M1 = 2;break;
          case 2:M2 = 2;break;
          case 3:M4 = 2;break;
      }

      if (mcto == 1 || mcto==3 || mcto ==5 || mcto == 7 ||mcto == 9 || mcto ==11|| mcto==13) 	{M1++;}

      if (mcto == 2 || mcto==3 || mcto ==6 || mcto == 7 ||mcto == 10 || mcto ==11|| mcto==14) {M2++;}

      if (mcto == 4 || mcto==5 || mcto ==6 || mcto == 7 ||mcto == 12 || mcto ==13|| mcto==14) {M4++;}

      if (mcto > 7) {M8++;}

    
      var canvas = document.getElementById("canvas");
      if (canvas.getContext) {
        var ctx = canvas.getContext("2d");

        ancho = canvas.width
        alto = canvas.height

      
      

      let colores = [[244,180,0],[15,157,88],[66,133,244],[219,68,55]] // amrillo,verde,azul, rojo
          
      if (colores[1] == colores[2]) {console.log("toma igual")} else {console.log("diferente")}


 //h1

 if (colores_a[0] != colores[H1] ) { for (var i = 0; i < 3; i++) 
  
    {
      if (colores_a[0][i] - colores[H1][i]  > 0) {colores_a[0][i]= colores_a[0][i] - 4};
      if (colores_a[0][i] - colores[H1][i]  < 0) {colores_a[0][i]= colores_a[0][i] + 4};
      if (Math.abs(colores_a[0][i] - colores[H1][i] )  < 6) {colores_a[0][i]=colores[H1][i]};

       }}

 ctx.fillStyle =  (`rgba(${colores_a[0]}`);
 ctx.beginPath();
 ctx.moveTo(ancho/2, alto/2);
 ctx.lineTo(ancho/2, 0);
 ctx.lineTo(ancho, alto/2);
 ctx.fill();


 
 //h2

 if (colores_a[1] != colores[H2] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[1][i] - colores[H2][i]  > 0) {colores_a[1][i]= colores_a[1][i] - 4};
    if (colores_a[1][i] - colores[H2][i]  < 0) {colores_a[1][i]= colores_a[1][i] + 4};
    if (Math.abs(colores_a[1][i] - colores[H2][i] )  < 6) {colores_a[1][i]=colores[H2][i]};

     }}


 ctx.fillStyle = (`rgba(${colores_a[1]}`);
 ctx.beginPath();
 ctx.moveTo(ancho/2, alto/2);
 ctx.lineTo(ancho, alto/2);
 ctx.lineTo(ancho/2, alto);
 ctx.fill();

 //h4

 if (colores_a[2] != colores[H4] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[2][i] - colores[H4][i]  > 0) {colores_a[2][i]= colores_a[2][i] - 4};
    if (colores_a[2][i] - colores[H4][i]  < 0) {colores_a[2][i]= colores_a[2][i] + 4};
    if (Math.abs(colores_a[2][i] - colores[H4][i] )  < 6) {colores_a[2][i]=colores[H4][i]};

     }}



 ctx.fillStyle = (`rgba(${colores_a[2]}`);
 ctx.beginPath();
 ctx.moveTo(ancho/2, alto/2);
 ctx.lineTo(0, alto/2);
 ctx.lineTo(ancho/2, alto);
 ctx.fill();
 
 //h8

 if (colores_a[3] != colores[H8] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[3][i] - colores[H8][i]  > 0) {colores_a[3][i]= colores_a[3][i] - 4};
    if (colores_a[3][i] - colores[H8][i]  < 0) {colores_a[3][i]= colores_a[3][i] + 4};
    if (Math.abs(colores_a[3][i] - colores[H8][i] )  < 6) {colores_a[3][i]=colores[H8][i]};

     }}


 ctx.fillStyle = (`rgba(${colores_a[3]}`);
 ctx.beginPath();
 ctx.moveTo(ancho/2, alto/2);
 ctx.lineTo(0, alto/2);
 ctx.lineTo(ancho/2, 0);
 ctx.fill();


 //m1

 if (colores_a[4] != colores[M1] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[4][i] - colores[M1][i]  > 0) {colores_a[4][i]= colores_a[4][i] - 4};
    if (colores_a[4][i] - colores[M1][i]  < 0) {colores_a[4][i]= colores_a[4][i] + 4};
    if (Math.abs(colores_a[4][i] - colores[M1][i] )  < 6) {colores_a[4][i]=colores[M1][i]};

     }}

 ctx.fillStyle = (`rgba(${colores_a[4]}`);  
 ctx.beginPath();
 ctx.moveTo(ancho/2, 0);
 ctx.lineTo(ancho,0);
 ctx.lineTo(ancho, alto/2);
 ctx.fill();

 //m2


 if (colores_a[5] != colores[M2] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[5][i] - colores[M2][i]  > 0) {colores_a[5][i]= colores_a[5][i] - 4};
    if (colores_a[5][i] - colores[M2][i]  < 0) {colores_a[5][i]= colores_a[5][i] + 4};
    if (Math.abs(colores_a[5][i] - colores[M2][i] )  < 6) {colores_a[5][i]=colores[M2][i]};

     }}

 ctx.fillStyle = (`rgba(${colores_a[5]}`);
 ctx.beginPath();
 ctx.moveTo(ancho, alto/2);
 ctx.lineTo(ancho/2, alto);
 ctx.lineTo(ancho, alto);
 ctx.fill();
 
 //m4

 console.log("M4 "+M4);


 if (colores_a[6] != colores[M4] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[6][i] - colores[M4][i]  > 0) {colores_a[6][i]= colores_a[6][i] - 4};
    if (colores_a[6][i] - colores[M4][i]  < 0) {colores_a[6][i]= colores_a[6][i] + 4};
    if (Math.abs(colores_a[6][i] - colores[M4][i] )  < 16) {colores_a[6][i]=colores[M4][i]};

     }}




     //console.log("M4_a "+M4_a);
     console.log("M4 "+M4);

 ctx.fillStyle = (`rgba(${colores_a[6]}`);
 ctx.beginPath();
 ctx.moveTo(0, alto/2);
 ctx.lineTo(0, alto);
 ctx.lineTo(ancho/2, alto);
 ctx.fill();

//m8


if (colores_a[7] != colores[M8] ) { for (var i = 0; i < 3; i++) 
  
  {
    if (colores_a[7][i] - colores[M8][i]  > 0) {colores_a[7][i]= colores_a[7][i] - 4};
    if (colores_a[7][i] - colores[M8][i]  < 0) {colores_a[7][i]= colores_a[7][i] + 4};
    if (Math.abs(colores_a[7][i] - colores[M8][i] )  < 6) {colores_a[7][i]=colores[M8][i]};

     }}



 ctx.fillStyle = (`rgba(${colores_a[7]}`);;
 ctx.beginPath();
 ctx.moveTo(0,0);
 ctx.lineTo(ancho/2, 0);
 ctx.lineTo(0, alto/2);
 ctx.fill();


  ctx.beginPath();
  ctx.lineWidth= ancho*3/160;
  ctx.strokeStyle = "white";

  ctx.moveTo((ancho/2)+ancho/22, alto/2 );
  ctx.quadraticCurveTo(ancho/2, alto/2, ancho/2, alto/2-alto/22); // pto control, luego punto final
  
  ctx.moveTo((ancho/2)+ancho/22, alto/2 );
  ctx.quadraticCurveTo(ancho/2, alto/2, ancho/2, alto/2+alto/22);

  ctx.moveTo((ancho/2)-ancho/22, alto/2 );
  ctx.quadraticCurveTo(ancho/2, alto/2, ancho/2, alto/2-alto/22);

  ctx.moveTo((ancho/2)-ancho/22, alto/2 );
  ctx.quadraticCurveTo(ancho/2, alto/2, ancho/2, alto/2+alto/22);

  ctx.moveTo(0+ancho/22,0);
  ctx.quadraticCurveTo(0,0, 0, 0+alto/22);

  ctx.moveTo(ancho-ancho/22, 0 );
  ctx.quadraticCurveTo(ancho, 0, ancho, 0+alto/22);

  ctx.moveTo(0, alto-alto/22 );
  ctx.quadraticCurveTo(0, alto, 0+ancho/22, alto);

  ctx.moveTo((ancho)-ancho/22, alto );
  ctx.quadraticCurveTo(ancho, alto, ancho, alto-alto/22);

  ctx.moveTo(0, 0);
  ctx.lineTo(0, alto);
  ctx.lineTo(ancho, alto);
  ctx.lineTo(ancho, 0);
  ctx.lineTo(0, 0);
  ctx.lineTo(0, alto);

  ctx.moveTo(0, alto/2);
  ctx.lineTo(ancho/2, 0);
  ctx.lineTo(ancho, alto/2);
  ctx.lineTo(ancho/2, alto);
  ctx.lineTo(0, alto/2);
  ctx.lineTo(ancho, alto/2);
  ctx.moveTo(ancho/2, alto);
  ctx.lineTo(ancho/2, 0);
  
  ctx.stroke();
 
      }


      } }
