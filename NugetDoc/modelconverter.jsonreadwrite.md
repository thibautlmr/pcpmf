# JsonReadWrite

Namespace: ModelConverter

Utility class for converting [MathParameters](./modelconverter.mathparameters.md) objects into json strings

```csharp
public static class JsonReadWrite
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [JsonReadWrite](./modelconverter.jsonreadwrite.md)

## Methods

### **FromJson(String)**

```csharp
internal static MathParameters FromJson(string jsonDescr)
```

#### Parameters

`jsonDescr` [String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

#### Returns

[MathParameters](./modelconverter.mathparameters.md)<br>

### **ToJson(MathParameters)**

Convert a [MathParameters](./modelconverter.mathparameters.md) object into a json string

```csharp
public static string ToJson(MathParameters mathParams)
```

#### Parameters

`mathParams` [MathParameters](./modelconverter.mathparameters.md)<br>

#### Returns

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>
