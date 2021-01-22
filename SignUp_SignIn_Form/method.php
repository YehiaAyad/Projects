<html>
<link rel="stylesheet" href="styles.css">
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.11.0/jquery.min.js"></script>
<body class="body1">
 <?php
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "users";
session_start();
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$x = $_POST["name"];
$y = $_POST["email"];    
$w = $_POST["pass"];
$z=md5($w);
$query="SELECT * from users where email='$y'";
$result=$conn->query($query);
    if(mysqli_num_rows($result)>0)
    { 
echo "This Email already exists. You will be redirected to the Login Page...........";
        echo "<script>setTimeout(\"location.href = 'signin.html';\",2500);</script>";
    }
    else 
   { 
$sql = "INSERT INTO users (name, email, password)
VALUES ('$x','$y','$z')";

if ($conn->query($sql) === TRUE) {
  echo "New record created successfully with name : $x ";
    $_SESSION["newsession"]=$x;
    echo "<script>setTimeout(\"location.href = 'final.php';\",2500);</script>";
    
    
} else {
  echo "Error: " . $sql . "<br>" . $conn->error;
}
    }
$conn->close();
?>
    


</body>
</html>