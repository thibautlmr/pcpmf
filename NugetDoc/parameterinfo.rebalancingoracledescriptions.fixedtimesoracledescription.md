# FixedTimesOracleDescription

Namespace: ParameterInfo.RebalancingOracleDescriptions

Container class for an oracle that rebalances a portfolio at a regular frequency of data feeds.

```csharp
public class FixedTimesOracleDescription : IRebalancingOracleDescription
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [FixedTimesOracleDescription](./parameterinfo.rebalancingoracledescriptions.fixedtimesoracledescription.md)<br>
Implements [IRebalancingOracleDescription](./parameterinfo.rebalancingoracledescriptions.irebalancingoracledescription.md)

## Properties

### **Period**

Rebalancing period

```csharp
public int Period { get; set; }
```

#### Property Value

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>

### **Type**

Rebalancing oracle type

```csharp
public RebalancingOracleType Type { get; }
```

#### Property Value

[RebalancingOracleType](./parameterinfo.rebalancingoracledescriptions.rebalancingoracletype.md)<br>

## Constructors

### **FixedTimesOracleDescription()**

Default constructor

```csharp
public FixedTimesOracleDescription()
```
