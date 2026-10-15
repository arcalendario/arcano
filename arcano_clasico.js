  ctx.beginPath();
  ctx.lineWidth = ancho * 3 / 160;

  // Detectar si el navegador está en modo oscuro
  if (window.matchMedia && window.matchMedia('(prefers-color-scheme: dark)').matches) {
      ctx.strokeStyle = "white"; // Líneas blancas para fondo negro en modo oscuro
  } else {
      ctx.strokeStyle = "#333333"; // Líneas oscuras para fondo blanco en modo claro
  }

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
