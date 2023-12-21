using MarketData;
using ParameterInfo;

namespace FinancialApp
{
    public class Handler
    {
        public Portfolio Portfolio { get; set; }
        public ComputationUtilities ComputationUtilities { get; set; }
        public DataFeed MarketDataPrevDate { get; set; }
        public DataFeed MarketDataCurrDate { get; set; }
        public List<string> Ids { get; set; }
        public DateTime PrevDate {  get; set; }
        public DateTime CurrDate { get; set; }


        public Handler(ComputationUtilities computationUtilities, DataFeed marketDataCurrDate)
        {
            ComputationUtilities = computationUtilities;
            MarketDataPrevDate = marketDataCurrDate;
            MarketDataCurrDate = marketDataCurrDate;
            Ids = ComputationUtilities.DataUtilities.GetIds();
            PrevDate = MarketDataPrevDate.Date;
            CurrDate = MarketDataCurrDate.Date;
            Portfolio = InitializePortfolioCompo();
        }

        private Portfolio InitializePortfolioCompo()
        {
            double[] deltas = ComputationUtilities.GetDeltas();
            Dictionary<String, double> compo = new();
            double freeRateQuantity = GetPortfolioValue();
            for (int i = 0; i < MarketDataCurrDate.SpotList.Count; i++)
            {
                compo.Add(Ids[i], deltas[i]);
                freeRateQuantity -= compo[Ids[i]] * MarketDataCurrDate.SpotList[Ids[i]];
            }
            return new Portfolio(compo, freeRateQuantity, 1);
        }

        public double GetPortfolioValue()
        {
            if (MarketDataPrevDate == MarketDataCurrDate)
            {
                return ComputationUtilities.GetPrice();
            }
            double portfolioValue = 0;
            for (int i = 0; i < MarketDataCurrDate.SpotList.Count; i++)
            {

                portfolioValue += Portfolio.Composition[Ids[i]] * MarketDataCurrDate.SpotList[Ids[i]];
            }
            Portfolio.FreeRate = ComputationUtilities.GetFreeRateBetweenTwoDates(PrevDate, CurrDate);
            portfolioValue += Portfolio.FreeRateQuantity * (1 + Portfolio.FreeRate);
            return portfolioValue;
        }

        public void UpdateCompo()
        {
            double total = GetPortfolioValue();
            for (int i = 0; i < MarketDataCurrDate.SpotList.Count; i++)
            {
                Portfolio.Composition[Ids[i]] = ComputationUtilities.GetDeltas()[i];
                total -= Portfolio.Composition[Ids[i]] * MarketDataCurrDate.SpotList[Ids[i]];
            }
            Portfolio.FreeRateQuantity = total;
            Portfolio.FreeRate = ComputationUtilities.GetFreeRateBetweenTwoDates(PrevDate, CurrDate);
        }

        public void AddOutputData(List<OutputData> outputDatas)
        {
            OutputData outputData = new()
            {
                Date = CurrDate,
                Value = GetPortfolioValue()
            };
            outputData.Deltas = ComputationUtilities.GetDeltas();
            outputData.DeltasStdDev = ComputationUtilities.GetDeltaStdDev();
            outputData.Price = ComputationUtilities.GetPrice();
            outputData.PriceStdDev = ComputationUtilities.GetPriceStdDev();
            outputDatas.Add(outputData);
        }
    }
}
