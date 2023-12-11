# ConditionalCallPayoffDescription

Namespace: ParameterInfo.PayoffDescriptions

Container class for the parameters describing the derivative product to cover.

```csharp
public class ConditionalCallPayoffDescription : Payoffs.Parameters.PayoffDescriptions.IPayoffDescription
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [ConditionalCallPayoffDescription](./parameterinfo.payoffdescriptions.conditionalcallpayoffdescription.md)<br>
Implements [IPayoffDescription](./payoffs.parameters.payoffdescriptions.ipayoffdescription.md)

## Properties

### **Type**

Type of the payoff

```csharp
public PayoffType Type { get; }
```

#### Property Value

[PayoffType](./payoffs.parameters.payoffdescriptions.payofftype.md)<br>

### **CreationDate**

Date at which the product starts being available

```csharp
public DateTime CreationDate { get; set; }
```

#### Property Value

[DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>

### **PaymentDates**

Dates at which the product potentially pays a cashflow

```csharp
public DateTime[] PaymentDates { get; set; }
```

#### Property Value

[DateTime[]](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>

### **Strikes**

Strikes for the conditional call

```csharp
public Double[] Strikes { get; set; }
```

#### Property Value

[Double[]](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>

## Constructors

### **ConditionalCallPayoffDescription()**

```csharp
public ConditionalCallPayoffDescription()
```
