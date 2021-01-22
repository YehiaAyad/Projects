<html>
    <link rel="stylesheet" href="styles.css">
<body class="body2">
 <?php
session_start();
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "department";

// Create connection
$conn = new mysqli($servername, $username, $password, $dbname);
// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
echo "Welcome ";
   echo $_SESSION["newsession"];
   

echo".<hr>";
    
$query="SELECT * from department";
$result=$conn->query($query);
    if ($result->num_rows > 0) {
  while($row = $result->fetch_assoc()) {
    echo "DEPT-Name: " . $row["name"]. " - Description: " . $row["description"]."<br>";
  }
} else {
  echo "0 results";
}
$conn->close();
?>
    


</body>
</html>