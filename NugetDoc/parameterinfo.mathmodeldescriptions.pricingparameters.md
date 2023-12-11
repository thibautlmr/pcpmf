# PricingParameters

Namespace: ParameterInfo.MathModelDescriptions

Container class for the pricing parameters

```csharp
public class PricingParameters
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [PricingParameters](./parameterinfo.mathmodeldescriptions.pricingparameters.md)

## Properties

### **UnderlyingPositions**

Correspondence between an underlying asset id and its position in the [PricingParameters.Volatilities](./parameterinfo.mathmodeldescriptions.pricingparameters.md#volatilities) or [PricingParameters.Correlations](./parameterinfo.mathmodeldescriptions.pricingparameters.md#correlations) arrays.

```csharp
public Dictionary<string, int> UnderlyingPositions { get; set; }
```

#### Property Value

[Dictionary&lt;String, Int32&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2)<br>

### **ForeignCurrencyPositions**

Correspondence between a foreign currency id and its position in the [PricingParameters.Volatilities](./parameterinfo.mathmodeldescriptions.pricingparameters.md#volatilities) or [PricingParameters.Correlations](./parameterinfo.mathmodeldescriptions.pricingparameters.md#correlations) arrays.

```csharp
public Dictionary<string, int> ForeignCurrencyPositions { get; set; }
```

#### Property Value

[Dictionary&lt;String, Int32&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2)<br>

### **Volatilities**

The volatilies to be used in the pricer

```csharp
public Double[] Volatilities { get; set; }
```

#### Property Value

[Double[]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **Correlations**

The correlations between the assets

```csharp
public Double[][] Correlations { get; set; }
```

#### Property Value

[Double[][]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

### **SampleNb**

The number of Monte Carlo samples

```csharp
public int SampleNb { get; set; }
```

#### Property Value

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>

### **RelativeFiniteDifferenceStep**

The finite difference step for the computation of delta.

```csharp
public double RelativeFiniteDifferenceStep { get; set; }
```

#### Property Value

[Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

## Constructors

### **PricingParameters()**

```csharp
public PricingParameters()
```
