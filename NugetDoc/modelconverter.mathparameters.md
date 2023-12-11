# MathParameters

Namespace: ModelConverter

Necessary parameters for the pricer construction

```csharp
public class MathParameters
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [MathParameters](./modelconverter.mathparameters.md)

## Properties

### **VolCholeskyLines**

Jagged array, each line is of the form sigma_i*L_i, where L_i is line n°i of the Cholesky decomposition of the correlation matrix

```csharp
public Double[][] VolCholeskyLines { get; set; }
```

#### Property Value

[Double[][]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **MathPaymentDates**

Mathematical version of the product payment dates

```csharp
public Double[] MathPaymentDates { get; set; }
```

#### Property Value

[Double[]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **Strikes**

Strikes for the considered product

```csharp
public Double[] Strikes { get; set; }
```

#### Property Value

[Double[]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **DomesticInterestRate**

The risk-free rate in the domestic currency

```csharp
public double DomesticInterestRate { get; set; }
```

#### Property Value

[Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **RelativeFiniteDifferenceStep**

The relative finite difference step for delta computations

```csharp
public double RelativeFiniteDifferenceStep { get; set; }
```

#### Property Value

[Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **SampleNb**

Number of samples for the Monte Carlo pricer

```csharp
public int SampleNb { get; set; }
```

#### Property Value

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>

## Constructors

### **MathParameters()**

```csharp
public MathParameters()
```
