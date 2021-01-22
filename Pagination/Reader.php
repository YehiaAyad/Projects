<?php
session_start();
$servername = "localhost";
$username = "root";
$password = "";
$dbname = "course";
$dbname1 = "department";
$dbname2 = "professor";
// Create connection
$conn = new mysqli($servername, $username, $password, $dbname); 
$conn1 = new mysqli($servername, $username, $password, $dbname1); 
$conn2 = new mysqli($servername, $username, $password, $dbname2); 

// Check connection
if ($conn->connect_error) {
  die("Connection failed: " . $conn->connect_error);
}
$query="SELECT * from course";
$result=$conn->query($query);
    
    if ($result->num_rows > 0) {
  while($row = $result->fetch_assoc()) {
$er= $row["department_id"];  
$er1=$row["professor_id"]; 

$query1="SELECT department_name from department where department_id='$er'";
$result1=$conn1->query($query1);    
$row1 = $result1->fetch_array(MYSQLI_NUM);

$query2="SELECT professor_name from professor where professor_id='$er1'";
$result2=$conn2->query($query2);   
$row2 = $result2->fetch_array(MYSQLI_NUM);
     // echo "Course Id:".$row["course_id"]."<br>"."Course name:".$row["course_name"]."<br>"."Course Description:".$row["course_description"]."<br>"."Department Id:".$row1[0]."<br>"."Professor Id:".$row2[0]."<hr>";
  }
} else {
  echo "0 results";
}

    ?>
    