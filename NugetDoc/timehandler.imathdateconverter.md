# IMathDateConverter

Namespace: TimeHandler

Interface for convertes that permit to convert a time distance into its mathematical counterpart.

```csharp
public interface IMathDateConverter
```

## Properties

### **WorkingDaysPerYear**

Convention on the number of business days in a year

```csharp
public abstract int WorkingDaysPerYear { get; }
```

#### Property Value

[Int32](https://docs.microsoft.com/en-us/dotnet/api/system.int32)<br>

## Methods

### **ConvertToMathDistance(DateTime, DateTime)**

Converts a time span into a mathematical time distance

```csharp
double ConvertToMathDistance(DateTime from, DateTime until)
```

#### Parameters

`from` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
Start date

`until` [DateTime](https://docs.microsoft.com/en-us/dotnet/api/system.datetime)<br>
End date

#### Returns

[Double](https://docs.microsoft.com/en-us/dotnet/api/system.double)<br>
The conversion of the time span
