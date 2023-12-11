# AssetsDescription

Namespace: ParameterInfo.MarketDescription

Description of the available assets on the market, the currency in which their prices are given, the risk-free rates for all currencies and the identifier of the domestic currency.

```csharp
public class AssetsDescription
```

Inheritance [Object](https://docs.microsoft.com/en-us/dotnet/api/system.object) → [AssetsDescription](./parameterinfo.marketdescription.assetsdescription.md)

## Properties

### **AssetCurrencyCorrespondence**

Associate a currency to each underlying

```csharp
public Dictionary<string, string> AssetCurrencyCorrespondence { get; set; }
```

#### Property Value

[Dictionary&lt;String, String&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2)<br>

### **CurrencyRates**

Associate a risk-free rate to each currency. Constraint: all currencies appearing in [AssetsDescription.AssetCurrencyCorrespondence](./parameterinfo.marketdescription.assetsdescription.md#assetcurrencycorrespondence) 
 must occur as keys of this dictionary.

```csharp
public Dictionary<string, double> CurrencyRates { get; set; }
```

#### Property Value

[Dictionary&lt;String, Double&gt;](https://docs.microsoft.com/en-us/dotnet/api/system.collections.generic.dictionary-2)<br>

### **DomesticCurrencyId**

Id of the domestic currency. Constraint: this id must occur as a key of [AssetsDescription.CurrencyRates](./parameterinfo.marketdescription.assetsdescription.md#currencyrates)

```csharp
public string DomesticCurrencyId { get; set; }
```

#### Property Value

[String](https://docs.microsoft.com/en-us/dotnet/api/system.string)<br>

## Constructors

### **AssetsDescription()**

Default constructor

```csharp
public AssetsDescription()
```
