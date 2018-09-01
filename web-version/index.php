<?php
	error_reporting(E_ALL);
	ini_set('display_errors', 1);
	if(isset($_POST["accion1"]))
	{
		set_time_limit (0);
		$address = 'localhost';
		$port = 4000;

		// Create the socket
		if(($sockd = socket_create(AF_INET, SOCK_STREAM,SOL_TCP))<1)
			die("Unable to create socket:" . socket_strerror(socket_last_error()));
		else
		//echo "Socket created ...\n";

		if(socket_connect($sockd,$address,$port) == FALSE)
			die("Unable to connect:" . socket_strerror(socket_last_error()));
		else
		//echo "Socket connected ...\n";

		$message = $_POST["query"];
		if(!socket_send( $sockd , $message , strlen($message) , 0))
		{
			$errorcode = socket_last_error();
			$errormsg = socket_strerror($errorcode);
			die("Could not send data: [$errorcode] $errormsg \n");
		}
		//echo "Message send successfully \n";
		// Now receive reply from server
		if(socket_recv( $sockd , $buf , 10240, MSG_WAITALL ) === FALSE)
		{
			$errorcode = socket_last_error();
			$errormsg = socket_strerror($errorcode);
			die("Could not receive data: [$errorcode] $errormsg \n");
		}
		//echo "Message received \n";
		// print the received message
		//echo $buf;
		$resultados = explode("@", $buf);
		//var_dump($buf);
		socket_close($sockd);
	}
	else
	{
		$_POST["query"]="";
	}

?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="utf-8" />
    <title>MOTOR DE BÚSQUEDA USANDO RADIX TREE</title>
    <script src="https://code.jquery.com/jquery-3.3.1.min.js"></script>
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <link rel="stylesheet" href="css/materialize.min.css">
    <link href="https://fonts.googleapis.com/icon?family=Material+Icons" rel="stylesheet">
    <link type="text/css" rel="stylesheet" href="css/materialize.min.css"  media="screen,projection"/>
    <link type="text/css" rel="stylesheet" href="css/style.css"/>
    <script type="text/javascript" src="dependencies/jquery-2.1.1.min.js"></script>
    <script type="text/javascript" src="dependencies/materialize.min.js"></script>
    <script type="text/javascript" src="dependencies/fabric.min.js"></script>

<style>
#b_container {
		height: 100%;
		min-height: 1400px;

}
</style>
  <nav class="grey darken-4">
    <div class="nav-wrapper">
        <a href="#" class="brand-logo center">VIAV</a>
    </div>
  </nav>
  </head>


  <body>
    <div class="container row" id="b_container">

      <div class="col s5 grey lighten-5 center-align full-width"><h3>Búsqueda:</h3>
	<form role="form" method="POST" action="index.php" id="ingresar" name="ingresar">
		<div class="top_b_space" id="searchbox" style="float:up;">
          <div class="input-field">
            <i class="material-icons prefix">search</i>
            <input id="query" oninput="this.value=this.value.toLowerCase()" name='query' type="text" class="validate" <?php echo "value='".$_POST["query"]."'"; ?> >
						<input type="hidden" id="accion1" name='accion1' value='1'>
            <label for="query">Ingresar palabras</label>
          </div>
          <div>
            <button class="btn grey" type="submit" name="action">Buscar con VIAV</button>
          </div>
      	</div>
	</form>


	<div id="search_results" style="float:down">
		<fieldset class="top_b_space" id="field_results">
			<legend><h3>Documentos:</h3></legend>
			<div id=search_list>

				<?php
					if(isset($_POST["accion1"])){
						echo "<h4>".$resultados[0]."</h4><br>";
						echo  '<ul class="collection">';
						for($i = 1; $i < count($resultados); $i++){
								echo "<li class='collection-item'><a href='https://es.wikipedia.org/wiki/".$resultados[$i]."'>".$resultados[$i]."</a><br></li>";
						}
						echo "</ul>";
					}
				?>

			</div>
	</fieldset>
</div>

    </div>

    <div class="col s7 grey lighten-5 center-align full-width"><h3>Contenido:</h3>
      <fieldset>
      <center>
        <div id="text_result">



        </div>
      </center>
    </fieldset>
    </div>


  </div>
  </body>
  <script type="text/javascript" src="js/main.js"></script>
  <script type="text/javascript" src="js/polygon.js"></script>
  <script type="text/javascript" src="js/point.js"></script>
  <script type="text/javascript" src="js/mqtt.js"></script>
	</html>
