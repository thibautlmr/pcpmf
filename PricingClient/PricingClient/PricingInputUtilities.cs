using Google.Protobuf;
using GrpcPricing.Protos;
using TimeHandler;

namespace FinancialApp
{
    internal class PricingInputUtilities
    {
        public DataUtilities DataUtilities { get; set; }
        public PricingInputUtilities(DataUtilities dataUtilities)
        {
            DataUtilities = dataUtilities;
        }

        double GetElapsedTime(DateTime date)
        {
            int numberOfDaysInOneYear = DataUtilities.TestParameters.NumberOfDaysInOneYear;
            DateTime firstDate = DataUtilities.MarketData[0].Date;
            MathDateConverter mathDateConverter = new(numberOfDaysInOneYear);
            return mathDateConverter.ConvertToMathDistance(firstDate, date);
        }

        bool IsMonitoringDateReached(DateTime date)
        {
            DateTime[] paymentDates = DataUtilities.TestParameters.PayoffDescription.PaymentDates;
            for (int i = 0; i < paymentDates.Length; i++)
            {
                if (paymentDates[i].Date == date)
                {
                    return true;
                }
            }
            return false;
        }  

        public PricingInput CreatePricingInput()
        {
            List<PastLines> pastLines = new();
            double[] spots = DataUtilities.GetSpots(DataUtilities.MarketData[0].Date);
            PastLines spotLine = new();
            for (int i = 0; i < spots.Length; i++)
            {
                spotLine.Value.Add(spots[i]);
            }
            pastLines.Add(spotLine);
            return new PricingInput() 
            { 
                Time = 0,
                MonitoringDateReached = false,
                Past = { pastLines }
            };
        }

        public void UpdatePricingInput(PricingInput pricingInput, DateTime date)
        {
            double[] spots = DataUtilities.GetSpots(date);
            PastLines spotLine = new();
            for (int i = 0; i < spots.Length; i++)
            {
                spotLine.Value.Add(spots[i]);
            }
            pricingInput.Past.Add(spotLine);
            pricingInput.Time = GetElapsedTime(date);
            pricingInput.MonitoringDateReached = IsMonitoringDateReached(date);
        }
    }
}
