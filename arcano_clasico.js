function transicionar(colorActual, colorObjetivo) {
  for (var i = 0; i < 3; i++) {
    var diff = colorObjetivo[i] - colorActual[i];
    
    // Si la diferencia es muy chiquita, lo posamos directamente en el objetivo
    if (Math.abs(diff) < 1) {
      colorActual[i] = colorObjetivo[i];
    } else {
      // Avanza proporcionalmente a la distancia (rápido al principio, frenando suavemente)
      colorActual[i] += diff * 0.15;
      colorActual[i] = Math.round(colorActual[i]);
    }
  }
}

function arcano_clasico () {

  var H1=0; var H2=0; var H4=0; var H8=0;
  var M1=0; var M2=0; var M4=0; var M8=0;

  let f = new Date();
  var hora = f.getHours();
  var min = f.getMinutes();

  var cuarthora = Math.floor(hora / 15);
  var hcto = Math.floor(hora - cuarthora * 15);

  var cuartminuto = Math.floor(min / 15);
  var mcto = Math.floor(min - cuartminuto * 15);

  if (min != min_a) {

    console.log("entro");

    // hora
    if (cuarthora == 1) { H1 = 2 } else { H1 = 0 }
    if (hcto == 1 || hcto == 3 || hcto == 5 || hcto == 7 || hcto == 9 || hcto == 11 || hcto == 13) { H1++; }
    if (hcto == 2 || hcto == 3 || hcto == 6 || hcto == 7 || hcto == 10 || hcto == 11 || hcto == 14) { H2++; }
    if (hcto == 4 || hcto == 5 || hcto == 6 || hcto == 7 || hcto == 12 || hcto == 13 || hcto == 14) { H4++; }
    if (hcto > 7) { H8++; }

    /// minutos
    switch(cuartminuto){ 
      case 1: M1 = 2; break;
      case 2: M2 = 2; break;
      case 3: M4 = 2; break;
    }

    if (mcto == 1 || mcto == 3 || mcto == 5 || mcto == 7 || mcto == 9 || mcto == 11 || mcto == 13) { M1++; }
    if (mcto == 2 || mcto == 3 || mcto == 6 || mcto == 7 || mcto == 10 || mcto == 11 || mcto == 14) { M2++; }
    if (mcto == 4 || mcto == 5 || mcto == 6 || mcto == 7 || mcto == 12 || mcto == 13 || mcto == 14) { M4++; }
    if (mcto > 7) { M8++; }

    var canvas = document.getElementById("canvas");
    if (canvas.getContext) {
      var ctx = canvas.getContext("2d");

      var ancho = canvas.width;
      var alto = canvas.height;

      let colores = [[244,180,0],[15,157,88],[66,133,244],[219,68,55]]; // amarillo, verde, azul, rojo

      // h1
      transicionar(colores_a[0], colores[H1]);
      ctx.fillStyle = (`rgba(${colores_a[0]})`);
      ctx.beginPath();
      ctx.moveTo(ancho/2, alto/2);
      ctx.lineTo(ancho/2, 0);
      ctx.lineTo(ancho, alto/2);
      ctx.fill();

      // h2
      transicionar(colores_a[1], colores[H2]);
      ctx.fillStyle = (`rgba(${colores_a[1]})`);
      ctx.beginPath();
      ctx.moveTo(ancho/2, alto/2);
      ctx.lineTo(ancho, alto/2);
      ctx.lineTo(ancho/2, alto);
      ctx.fill();

      // h4
      transicionar(colores_a[2], colores[H4]);
      ctx.fillStyle = (`rgba(${colores_a[2]})`);
      ctx.beginPath();
      ctx.moveTo(ancho/2, alto/2);
      ctx.lineTo(0, alto/2);
      ctx.lineTo(ancho/2, alto);
      ctx.fill();

      // h8
      transicionar(colores_a[3], colores[H8]);
      ctx.fillStyle = (`rgba(${colores_a[3]})`);
      ctx.beginPath();
      ctx.moveTo(ancho/2, alto/2);
      ctx.lineTo(0, alto/2);
      ctx.lineTo(ancho/2, 0);
      ctx.fill();

      // m1
      transicionar(colores_a[4], colores[M1]);
      ctx.fillStyle = (`rgba(${colores_a[4]})`);  
      ctx.beginPath();
      ctx.moveTo(ancho/2, 0);
      ctx.lineTo(ancho, 0);
      ctx.lineTo(ancho, alto/2);
      ctx.fill();

      // m2
      transicionar(colores_a[5], colores[M2]);
      ctx.fillStyle = (`rgba(${colores_a[5]})`);
      ctx.beginPath();
      ctx.moveTo(ancho, alto/2);
      ctx.lineTo(ancho/2, alto);
      ctx.lineTo(ancho, alto);
      ctx.fill();

      // m4
      transicionar(colores_a[6], colores[M4]);
      ctx.fillStyle = (`rgba(${colores_a[6]})`);
      ctx.beginPath();
      ctx.moveTo(0, alto/2);
      ctx.lineTo(0, alto);
      ctx.lineTo(ancho/2, alto);
      ctx.fill();

      // m8
      transicionar(colores_a[7], colores[M8]);
      ctx.fillStyle = (`rgba(${colores_a[7]})`);
      ctx.beginPath();
      ctx.moveTo(0, 0);
      ctx.lineTo(ancho/2, 0);
      ctx.lineTo(0, alto/2);
      ctx.fill();

      // Líneas divisorias y bordes
      ctx.beginPath();
      ctx.lineWidth = ancho * 5 / 160;
      ctx.strokeStyle = window.getComputedStyle(document.body).backgroundColor;

      ctx.moveTo((ancho/2)+ancho/22, alto/2 );
      ctx.quadraticCurveTo(ancho/2, alto/2, ancho/2, alto/2-alto/22); 

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
  } 
}
