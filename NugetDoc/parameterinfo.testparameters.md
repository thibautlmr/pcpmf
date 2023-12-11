# TestParameters

Namespace: ParameterInfo

Container class with the entire description of the parameters necessary for running a test.

```csharp
public class TestParameters
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [TestParameters](./parameterinfo.testparameters.md)

## Properties

### **AssetDescription**

Property containing the asset descriptions

```csharp
public AssetsDescription AssetDescription { get; set; }
```

#### Property Value

[AssetsDescription](./parameterinfo.marketdescription.assetsdescription.md)<br>

### **RebalancingOracleDescription**

Property containing the rebalancing oracle descriptions

```csharp
public FixedTimesOracleDescription RebalancingOracleDescription { get; set; }
```

#### Property Value

[FixedTimesOracleDescription](./parameterinfo.rebalancingoracledescriptions.fixedtimesoracledescription.md)<br>

### **NumberOfDaysInOneYear**

Convention on the number of business days in a year

```csharp
public int NumberOfDaysInOneYear { get; set; }
```

#### Property Value

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>

### **PayoffDescription**

Description of the product to hedge

```csharp
public ConditionalCallPayoffDescription PayoffDescription { get; set; }
```

#### Property Value

[ConditionalCallPayoffDescription](./parameterinfo.payoffdescriptions.conditionalcallpayoffdescription.md)<br>

### **PricingParams**

Parameters that are used by the pricer

```csharp
public PricingParameters PricingParams { get; set; }
```

#### Property Value

[PricingParameters](./parameterinfo.mathmodeldescriptions.pricingparameters.md)<br>

## Constructors

### **TestParameters()**

Default constructor

```csharp
public TestParameters()
```
