package com.example.matrixcalc

import android.os.Bundle
import android.widget.*
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    external fun operateMatrices(
        mat1: Array<DoubleArray>,
        mat2: Array<DoubleArray>,
        opCode: Int
    ): Array<DoubleArray>

    companion object {
        init {
            System.loadLibrary("matrix_lib")
        }
    }

    private fun parseMatrix(input: String): Array<DoubleArray> {
        val rows = input.trim().lines().filter { it.isNotBlank() }

        val matrix = mutableListOf<DoubleArray>()
        var expectedCols = -1

        for ((i, rowText) in rows.withIndex()) {
            val cols = rowText.split(",").map { it.trim() }

            if (expectedCols == -1) expectedCols = cols.size
            if (cols.size != expectedCols) {
                throw IllegalArgumentException("Row ${i + 1} has ${cols.size} columns. Expected $expectedCols.")
            }

            val numbers = cols.map {
                it.toDoubleOrNull() ?: throw IllegalArgumentException("Invalid number '${it}' in row ${i + 1}.")
            }

            matrix.add(numbers.toDoubleArray())
        }

        return matrix.toTypedArray()
    }

    private fun matrixToString(matrix: Array<DoubleArray>): String {
        return matrix.joinToString("\n") { row ->
            row.joinToString(", ")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val matrixInput1 = findViewById<EditText>(R.id.matrixInput1)
        val matrixInput2 = findViewById<EditText>(R.id.matrixInput2)
        val spinner = findViewById<Spinner>(R.id.operationSpinner)
        val resultView = findViewById<TextView>(R.id.resultView)
        val calculateBtn = findViewById<Button>(R.id.calculateBtn)

        spinner.adapter = ArrayAdapter(
            this,
            android.R.layout.simple_spinner_dropdown_item,
            arrayOf("Add", "Subtract", "Multiply", "Divide")
        )

        calculateBtn.setOnClickListener {
            try {
                val mat1 = parseMatrix(matrixInput1.text.toString())
                val mat2 = parseMatrix(matrixInput2.text.toString())
                val opCode = spinner.selectedItemPosition

                // Validation based on operation
                when (opCode) {
                    0, 1, 3 -> { // Add, Subtract, Divide
                        if (mat1.size != mat2.size || mat1[0].size != mat2[0].size) {
                            resultView.text =
                                "Error: Matrices must have the same dimensions for ${spinner.selectedItem}.\nMatrix 1: ${mat1.size}x${mat1[0].size}, Matrix 2: ${mat2.size}x${mat2[0].size}"
                            return@setOnClickListener
                        }
                    }

                    2 -> { // Multiply
                        if (mat1[0].size != mat2.size) {
                            resultView.text =
                                "Error: Cannot multiply ${mat1.size}x${mat1[0].size} × ${mat2.size}x${mat2[0].size}.\nColumns of Matrix 1 must equal rows of Matrix 2."
                            return@setOnClickListener
                        }
                    }
                }

                val result = operateMatrices(mat1, mat2, opCode)
                resultView.text = matrixToString(result)

            } catch (e: Exception) {
                resultView.text = "Error: ${e.message}"
            }
        }
    }
}
