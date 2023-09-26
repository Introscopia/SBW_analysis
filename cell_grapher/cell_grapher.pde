

void setup() {
   size(400, 400);
   noLoop();
}

void draw() {
  background(255);
  int m = 20;
  int e = 20;
  
  String dataset = "333x2600";
    
  String[] data = loadStrings(dataset+".txt");
  int[] V = new int[data.length];
  int[] R = new int[data.length];
  int vmax = 0;
  int rmax = 0;
  println( data.length );
  for(int i = 0; i < data.length; i++){
     String[] spl = split(data[i], ',');
     V[i] = int(spl[0]);
     R[i] = int(trim(spl[1]));
     if( V[i] > vmax ) vmax = V[i];
     if( R[i] > rmax ) rmax = R[i];
  }
  println( vmax, rmax );
  if( vmax < 19 ) vmax = 19;
  if( rmax < 19 ) rmax = 19;
  
  int[][] grid = new int[vmax+1][rmax+1];
  int gmax = 0;
  for(int i=0; i < data.length; i++){
    grid[ V[i] ][ R[i] ] += 1;
    if( grid[ V[i] ][ R[i] ] > gmax ) gmax = grid[ V[i] ][ R[i] ];
  }
  println( gmax );
  noStroke();
  for(int i=0; i < vmax; i++){
     for(int j=0; j < rmax; j++){
        int G = round(map( grid[i][j], 0, gmax, 0, 255 ));
        fill( 0, G, 0 );
        rect( m + j*e, height-m -((i+1)*e), e , e);
     }
  }
  
  //for(int i=0; i < 20; i++){
  //      fill( #21291E );
  //      rect( m + i*e, height-m -((i+1)*e), e , e);    
  //}
  
  
  strokeWeight(1);
  stroke(60);
  for(int i = m; i < width; i += e){
    line( i, 0, i, height-m );
  }
  for(int j = height-m; j > 0; j -= e){
    line( m, j, width, j );
  }
  
  line( m, height-m, width, 0 );
  
  strokeWeight(2);
  stroke(80);
  line( m, 0, m, height-m );
  line( m, height-m, width, height-m );
  
  fill(0);
  noStroke();
  textAlign( CENTER, TOP );
  for(int i = m; i < width; i += e){
    text( ""+(i-m)/e, i+(e/2), height-m );
  }
  textAlign( RIGHT, CENTER );
  for(int j = height-m; j > 0; j -= e){
    text( ""+(18-((j-m)/e)), m-5, j-(e/2) );
  }
  
  save( dataset+".png" );
}
