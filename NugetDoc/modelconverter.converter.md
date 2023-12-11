# Converter

Namespace: ModelConverter

Utility class that extracts the necessary info from a [TestParameters](./parameterinfo.testparameters.md) object to create a [MathParameters](./modelconverter.mathparameters.md) object

```csharp
public static class Converter
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [Converter](./modelconverter.converter.md)

## Methods

### **Cholesky(Double[,])**

Computation of the Cholesky decomposition of a matrix

```csharp
internal static Double[,] Cholesky(Double[,] matrix)
```

#### Parameters

`matrix` [Double[,]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>
The matrix to decompose

#### Returns

[Double[,]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>
The lower triangular matrix obtained by the decomposition algorithm

#### Exceptions

[ArgumentException](https://docs.microsoft.com/en-us/dotnet/api/system.argumentexception)<br>
Thrown if the matrix is not positive-definite

### **Extract(TestParameters)**

Main extraction method

```csharp
public static MathParameters Extract(TestParameters testParameters)
```

#### Parameters

`testParameters` [TestParameters](./parameterinfo.testparameters.md)<br>
>The object from which the info will be extracted

#### Returns

[MathParameters](./modelconverter.mathparameters.md)<br>
The exrtacted math parameters
