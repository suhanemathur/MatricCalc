<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>MatrixCalc - Project README</title>
</head>
<body>

<h1>MatrixCalc</h1>

<p><strong>MatrixCalc</strong> is a simple Android application designed to perform basic matrix operations — <strong>Addition</strong>, <strong>Subtraction</strong>, <strong>Multiplication</strong>, and <strong>Element-wise Division</strong> — on two user-input matrices. The core matrix operations are implemented natively in C++ using JNI (Java Native Interface) for improved performance.</p>

<hr>

<h2>Features</h2>
<ul>
    <li>Enter two matrices manually (comma-separated values for each row).</li>
    <li>Choose the operation: Add, Subtract, Multiply, or Divide.</li>
    <li>View calculated result immediately.</li>
    <li>Input validation for compatible matrix dimensions.</li>
    <li>Native C++ backend for fast matrix computation.</li>
</ul>

<hr>

<h2>Project Structure</h2>
<ul>
    <li><strong>MainActivity.kt</strong>: Handles user input, validates matrices, calls native C++ functions, and displays results.</li>
    <li><strong>matrix_lib.cpp</strong>: C++ implementation for matrix operations, interfaced via JNI.</li>
    <li><strong>matrix_lib.h</strong>: JNI header file for function declarations.</li>
</ul>

<hr>

<h2>How It Works</h2>
<ol>
    <li>User inputs two matrices as text.</li>
    <li>User selects the operation from a dropdown menu (Spinner).</li>
    <li>App validates matrix dimensions based on the selected operation.</li>
    <li>Matrices are passed to the C++ function <code>operateMatrices</code> through JNI.</li>
    <li>The C++ function performs the computation and returns the result matrix.</li>
    <li>The result is formatted and displayed in the app.</li>
</ol>

<hr>

<h2>Matrix Operation Details</h2>
<ul>
    <li><strong>Addition:</strong> Element-wise addition of two matrices. Dimensions must match.</li>
    <li><strong>Subtraction:</strong> Element-wise subtraction of two matrices. Dimensions must match.</li>
    <li><strong>Multiplication:</strong> Standard matrix multiplication. Columns of Matrix 1 must equal rows of Matrix 2.</li>
    <li><strong>Division:</strong> Element-wise division. Dimensions must match. Division by zero is safely handled.</li>
</ul>



</body>
</html>
