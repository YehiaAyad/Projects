<html>
<link rel="stylesheet" href="styles.css">
 <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
<body class="body1">
 <?php
session_start();
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "users";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}    
$y = $_POST["email"];
$w = $_POST["pass"];
$z=md5("$w");
    
$query="SELECT * FROM users WHERE email='$y' AND password='$z'";
    $result=$conn->query($query);
  if(mysqli_num_rows($result)>0)
    {  while($row = $result->fetch_assoc()) {
    $x=$row["name"];}
     $_SESSION["newsession"]=$x;
     echo "<script>setTimeout(\"location.href = 'final.php';\",0);</script>";
    }
     else 
   {  
        echo "WRONG CREDENTIALS. You will be redirected to the LOGIN Page...........";
        echo "<script>setTimeout(\"location.href = 'signin.html';\",2500);</script>";

    }
    

$conn->close();
?>
    


</body>
</html>