<?php

include "Reader.php";

$response = array();
$response1 = array();
$query = "SELECT * FROM course ORDER BY course_id";

$result = mysqli_query($conn,$query);
$i=1;
$y=1;
$z=1;
$y1=1;
$z1=1;
$page = 1;
if(!empty($_GET["page"])) {
	$page = $_GET["page"];
	}
$search="";
if(!empty($_GET["search"])) {
	$search = $_GET["search"];
	}
if($search=="")
{while($row = mysqli_fetch_array($result)){
$er= $row['department_id'];  
$er1=$row['professor_id']; 
    
$query1="SELECT department_name from department where department_id='$er'";
$result1=mysqli_query($conn1,$query1);;    
$row1 = $result1->fetch_array(MYSQLI_NUM);

$query2="SELECT professor_name from professor where professor_id='$er1'";
$result2=mysqli_query($conn2,$query2);;   
$row2 = $result2->fetch_array(MYSQLI_NUM);    
     
    $course_id = $row['course_id'];
    $course_name = $row['course_name'];
    $course_description = $row['course_description'];
    $department_name = $row1[0];
    $professor_name = $row2[0];
    $record_num = $i;
    
    if($y==$page)
    {$response[] = array('course_id' => $course_id,
                    'course_name' => $course_name,
                    'course_description' => $course_description,
                    'department_name' => $department_name,
                    'professor_name' => $professor_name,
                    'record_num' => $record_num ,
                    'record_page'=>$y);}
    
    if($z==5)
    {$y=$y+1;
    $z=1;}
    else 
    $z=$z+1;    
$i=$i+1;}
}
else {
        while($row = mysqli_fetch_array($result)){
$er= $row['department_id'];  
$er1=$row['professor_id']; 
    
$query1="SELECT department_name from department where department_id='$er'";
$result1=mysqli_query($conn1,$query1);;    
$row1 = $result1->fetch_array(MYSQLI_NUM);

$query2="SELECT professor_name from professor where professor_id='$er1'";
$result2=mysqli_query($conn2,$query2);;   
$row2 = $result2->fetch_array(MYSQLI_NUM);    
$q=0;
    $course_id = $row['course_id'];
    $course_name = $row['course_name'];
    $course_description = $row['course_description'];
    $department_name = $row1[0];
    $professor_name = $row2[0];
            
     $course_name1=$course_name;       
    $course_name1=strtolower($course_name1);
    $course_name1=str_replace(" ","",$course_name1);
    
    $course_description1=$course_description;
    $course_description1=strtolower($course_description1);
    $course_description1=str_replace(" ","",$course_description1);
    
    $department_name1=$department_name;
    $department_name1=strtolower($department_name1);
    $department_name1=str_replace(" ","",$department_name1);
       
    $professor_name1=$professor_name;        
    $professor_name1=strtolower($professor_name1);
    $professor_name1=str_replace(" ","",$professor_name1);
    
    $search1=$search;    
    $search1=strtolower($search1);
    $search1=str_replace(" ","",$search1);   
            
    if (strpos($search1, $course_name1) !== false || strpos($course_name1,$search1) !== false )
        $q=$q+1;
    
     if (strpos($search1, $course_description1) !== false || strpos($course_description1,$search1) !== false)
        $q=$q+1;
    
        if (strpos($search1, $department_name1) !== false || strpos($department_name1,$search1) !== false)
        $q=$q+1;
    
        if (strpos($search1,$professor_name1) !== false || strpos($professor_name1,$search1) !== false)
        $q=$q+1;
    $record_num = $i;
            //$y==$page &&
    if( $q>0)
    {   $response1[] = array('course_id' => $course_id,
                    'course_name' => $course_name,
                    'course_description' => $course_description,
                    'department_name' => $department_name,
                    'professor_name' => $professor_name,
                    'record_num' => $record_num ,
                    'record_page'=>$y);
    
    if($z==5)
    {$y=$y+1;
    $z=1;}
    else 
    $z=$z+1;    
$i=$i+1;}}
       foreach ($response1 as &$value) {
           {if( $value['record_page']==$page)
            array_push($response,$value);
}}
}
echo json_encode($response);

?>