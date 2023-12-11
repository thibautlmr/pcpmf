# IPayoffDescription

Namespace: Payoffs.Parameters.PayoffDescriptions

Common interface for all classes that contain descriptions of derivative products.

```csharp
public interface IPayoffDescription
```

## Properties

### **Type**

Type of the payoff

```csharp
public abstract PayoffType Type { get; }
```

#### Property Value

[PayoffType](./payoffs.parameters.payoffdescriptions.payofftype.md)<br>

### **CreationDate**

Date at which the product starts being available

```csharp
public abstract DateTime CreationDate { get; }
```

#### Property Value

[DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
